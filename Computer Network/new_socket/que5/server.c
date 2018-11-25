#include<stdio.h>
#include<string.h>  
#include<stdlib.h>  
#include<sys/socket.h>
#include<arpa/inet.h>
#include<unistd.h>   
#include<pthread.h>
#include<sys/select.h>
#include <fcntl.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/shm.h>
#include <sys/wait.h>
#include <signal.h>
#include <sys/poll.h>
#include <sys/time.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <pthread.h>
#include <sys/un.h>

int send_fd(int socket, int fd_to_send)
{
    struct msghdr socket_message;
    struct iovec io_vector[1];
    struct cmsghdr *control_message = NULL;
    char message_buffer[1];
    /* storage space needed for an ancillary element with a paylod of length is CMSG_SPACE(sizeof(length)) */
    char ancillary_element_buffer[CMSG_SPACE(sizeof(int))];
    int available_ancillary_element_buffer_space;

    /* at least one vector of one byte must be sent */
    message_buffer[0] = 'F';
    io_vector[0].iov_base = message_buffer;
    io_vector[0].iov_len = 1;

    /* initialize socket message */
    memset(&socket_message, 0, sizeof(struct msghdr));
    socket_message.msg_iov = io_vector;
    socket_message.msg_iovlen = 1;

    /* provide space for the ancillary data */
    available_ancillary_element_buffer_space = CMSG_SPACE(sizeof(int));
    memset(ancillary_element_buffer, 0, available_ancillary_element_buffer_space);
    socket_message.msg_control = ancillary_element_buffer;
    socket_message.msg_controllen = available_ancillary_element_buffer_space;

    /* initialize a single ancillary data element for fd passing */
    control_message = CMSG_FIRSTHDR(&socket_message);
    control_message->cmsg_level = SOL_SOCKET;
    control_message->cmsg_type = SCM_RIGHTS;
    control_message->cmsg_len = CMSG_LEN(sizeof(int));
    *((int *) CMSG_DATA(control_message)) = fd_to_send;

    int k=sendmsg(socket, &socket_message, 0);
    perror("sendmsg");
    return k;
 }
 int recv_fd(int socket)
 {
    int sent_fd, available_ancillary_element_buffer_space;
    struct msghdr socket_message;
    struct iovec io_vector[1];
    struct cmsghdr *control_message = NULL;
    char message_buffer[1];
    char ancillary_element_buffer[CMSG_SPACE(sizeof(int))];

    /* start clean */
    memset(&socket_message, 0, sizeof(struct msghdr));
    memset(ancillary_element_buffer, 0, CMSG_SPACE(sizeof(int)));

    /* setup a place to fill in message contents */
    io_vector[0].iov_base = message_buffer;
    io_vector[0].iov_len = 1;
    socket_message.msg_iov = io_vector;
    socket_message.msg_iovlen = 1;

    /* provide space for the ancillary data */
    socket_message.msg_control = ancillary_element_buffer;
    socket_message.msg_controllen = CMSG_SPACE(sizeof(int));

    recvmsg(socket, &socket_message, MSG_CMSG_CLOEXEC);
    perror("recvmsg");
    

    if(message_buffer[0] != 'F')
    {
        /* this did not originate from the above function */
        return -1;
    }

    if((socket_message.msg_flags & MSG_CTRUNC) == MSG_CTRUNC)
    {
        /* we did not provide enough space for the ancillary element array */
        return -1;
    }

    /* iterate ancillary elements */
    for(control_message = CMSG_FIRSTHDR(&socket_message);control_message != NULL;control_message = CMSG_NXTHDR(&socket_message,        control_message))
    {
        if( (control_message->cmsg_level == SOL_SOCKET) &&(control_message->cmsg_type == SCM_RIGHTS) )
        {
            sent_fd = *((int *) CMSG_DATA(control_message));
            return sent_fd;
        }
    }
    return -1;
}

int max(int a,int b)
{
if(a>b)return a;
return b;
}

char myfifo1[12]="ctos_fifo1";
int csfd[3];

void readpipe()
{
int i;
char buf[2000];
fd_set rfds;
struct timeval tv;
tv.tv_sec=0;tv.tv_usec=0;
int smax=0;
while(1)
{
for(i=0;i<3;i++)
{
FD_SET(csfd[i],&rfds);
smax=max(smax,csfd[i]);
}
int ret=select(smax+1,&rfds,NULL,NULL,(struct timeval *)&tv);
if(ret>=0)
{
for(i=0;i<3;i++)
{
if(FD_ISSET(csfd[i],&rfds))
{
   int n=read(csfd[i],buf,sizeof(buf));
   int no=buf[n-1]-'0';
   buf[n-1]='\0';
   printf("message from s%d from client%d : %s\n",i+1,no+1,buf);
      
}
}
}
}
exit(0);
}



int main()
{


//-------------CREATE INET SOCKET----------------//
int sfd[3],nsfd,size;
struct sockaddr_in server,client;
size=sizeof(server);
int port=7000,i;
for(i=0;i<1;i++)
{
sfd[i]=socket(AF_INET,SOCK_STREAM,0);
if(sfd[i]==-1)
{
printf("could not create socket\n");
exit(0);
}
server.sin_family=AF_INET;
server.sin_addr.s_addr=INADDR_ANY;
server.sin_port=htons(port+i);
if(bind(sfd[i],(struct sockaddr *)&server,sizeof(server))<0)
{
printf("bind failed inet\n");
exit(0);
}
listen(sfd[i],3);
perror("listen af_inet");
}
//-------------------------------------------------//

printf("SOCKET AF_INET CREATED\n");


//-----------CREATE UNIX SOCKET----------------------//
    char path[]="./demo_socket1";
    struct sockaddr_un address;
    int socket_fd[3], connection_fd[3];
    socklen_t address_length;
    pid_t child;
    
 for(i=0;i<3;i++)
 {
    socket_fd[i] = socket(PF_UNIX, SOCK_STREAM, 0);
    perror("socket");
     path[13]=i+'0';
    unlink(path);
    memset(&address, 0, sizeof(struct sockaddr_un));
    address.sun_family = AF_UNIX;
    snprintf(address.sun_path,sizeof(address.sun_path),"%s",path);
    bind(socket_fd[i], (struct sockaddr *) &address, sizeof(struct sockaddr_un));
    perror("bind");

    listen(socket_fd[i], 5);
    perror("listen");
 }
//-----------------------------------------------------// 
printf("SOCKET AF_UNIX CREATED\n");


//----------------CREATING PIPES--------------------//
for(i=0;i<3;i++)
{
   myfifo1[9]=(char)i+'0';
   myfifo1[10]='\0';
   mkfifo(myfifo1,0666);
   csfd[i]= open(myfifo1, O_RDWR);
   printf("pipe%d created\n",i);
}
//-------------------------------------------------//

pthread_t thr;
pthread_create(&thr,NULL,(void *)&readpipe,NULL);


char obj[]="s1";
int j;
for(i=0;i<3;i++)
{
obj[1]=i+1+'0';
int pid=fork();
if(pid==0)
{
printf("child \n");
char param[2];
int ppid=getppid();
sprintf(param,"%d",ppid);
execl(obj,obj,param,(char *)0);
}

}

for(i=0;i<3;i++)
{
if((connection_fd[i] = accept(socket_fd[i], (struct sockaddr *) &address,&address_length)) > -1)
{
printf("connection made with s%d\n",i+1);
write(connection_fd[i],"now serve the clients",strlen("now serve the clients"));
}
}


printf("STARTED: WAITING FOR CONNECTIONS\n");
fd_set rfds;
struct timeval tv;
tv.tv_usec=0;tv.tv_sec=0;
int smax=0;
char buf[200];

while(1)
{

    for(i=0;i<1;i++)
    {
        FD_SET(sfd[i],&rfds);
        smax=max(sfd[i],smax);
    }
    int retval=select(smax+1,&rfds,NULL,NULL,NULL);
    for(i=0;i<1;i++)
    {

        if(FD_ISSET(sfd[i],&rfds))
        {
           
               
                nsfd=accept(sfd[i],(struct sockaddr *)&client,&size);
                printf("connection accepted %d \n",nsfd);
                int j;
                read(nsfd,buf,sizeof(buf));
                j=buf[0]-'0';
                printf("client %d\n",j);
                int x=send_fd(connection_fd[j-1],nsfd);
                printf("hahahah %d\n", x);
            
        }
    }
}

  //close(sfd);
  //close(socket_fd);
  unlink("./demo_socket0");
  unlink("./demo_socket1");
  unlink("./demo_socket2");    
  return 0;
}
