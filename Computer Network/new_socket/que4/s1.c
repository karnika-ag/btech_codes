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

int flag[5]={0};
int sfd[3],size;
struct sockaddr_in server,client;

    char path[]="./demo_socket1";
    struct sockaddr_un address;
    int socket_fd[3], connection_fd[3];
    socklen_t address_length;
    pid_t child;

void rcvsfd(void *arg)
{
int no=*(int *)arg;
printf("thread no %d\n",no);
int n;
char buf[2000];
while(1)
{
   if(flag[no]==1)
   {
     printf("entered to accept in thr %d\n",no);
      flag[no]=0;
      int nsfd=accept(sfd[0],(struct sockaddr *)&client,&size);
      flag[no+1]=1;
      printf("connection accepted in s1 thr %d\n",no);
      write(nsfd,"i m assigned to u ..i'll repeat whatever u send\n",strlen("i m assigned to u ..i'll repeat whatever u send\n"));
      int num=0;
      while(1)
      {
        n=read(nsfd,buf,sizeof(buf));
        buf[n]='\0';
        write(nsfd,buf,strlen(buf));
        num++;
        if(num==5)
        break;
      }
      close(nsfd);
      flag[no]=1;   
   }
}
exit(0);
}

void specialthr(int no)
{
static int num=0;
int nsfd;
while(1)
{
  if(flag[no]==1)
  {
    printf("entered in specialthr\n");
    nsfd=accept(sfd[0],(struct sockaddr *)&client,&size);
    printf("connection accepted %d\n",connection_fd[0]);
    int x=send_fd(connection_fd[0],nsfd);
  }
}
exit(0);
}

int main()
{

size=sizeof(server);
//-------------CREATE INET SOCKET----------------//
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
    
 for(i=0;i<1;i++)
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


char obj[]="s1";
int j;
for(i=1;i<2;i++)
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

for(i=0;i<1;i++)
{
if((connection_fd[i] = accept(socket_fd[i], (struct sockaddr *) &address,&address_length)) > -1)
{
printf("connection made with s%d %d\n",i+1,connection_fd[i]);
write(connection_fd[i],"now serve the clients",strlen("now serve the clients"));
}
}


printf("STARTED: WAITING FOR CONNECTIONS\n");

flag[0]=1;
pthread_t thr[5];
int val[4]={0,1,2,3};
for(i=0;i<4;i++)
{
pthread_create(&thr[i],NULL,(void *)&rcvsfd,(void *)&val[i]);
printf("thread created\n");
}

specialthr(4);

  unlink("./demo_socket0");
  return 0;
}
