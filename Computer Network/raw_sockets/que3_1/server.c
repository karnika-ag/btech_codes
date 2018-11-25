#include<stdio.h>
#include<string.h>  
#include<stdlib.h>  
#include<sys/socket.h>
#include<arpa/inet.h>
#include<unistd.h>   
#include<pthread.h>
#include<sys/select.h>
#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/shm.h>
#include <sys/wait.h>
#include <signal.h>
#include <sys/poll.h>
#include <time.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/time.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <pthread.h>
#include <sys/un.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/ip.h>
#include <arpa/inet.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>


int flag[3]={0,0,0};
int *sno;
int max(int a,int b)
{
if(a>b)return a;
return b;
}

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
    for(control_message = CMSG_FIRSTHDR(&socket_message);control_message != NULL;control_message = CMSG_NXTHDR(&socket_message, control_message))
    {
        if( (control_message->cmsg_level == SOL_SOCKET) &&(control_message->cmsg_type == SCM_RIGHTS) )
        {
            sent_fd = *((int *) CMSG_DATA(control_message));
            return sent_fd;
        }
    }
    return -1;
}


void fun(int signo)
{
int y=sno[0];
flag[sno[0]]=0;
printf("flag[%d]=%d\n",sno[0],flag[sno[0]]); 
printf("train left platform %d\n",y);
signal(SIGUSR1,fun);
}

char *platname[3]={"TRAIN HAS ARRIVED PLATFORM 1","TRAIN HAS ARRIVED PLATFORM 2","TRAIN HAS ARRIVED PLATFORM 3"};

int main()
{
signal(SIGUSR1,fun);

//--------------------create shared memory-----//
int shmid;
key_t key=ftok(".",'a');
if((shmid=shmget(key,sizeof(int),IPC_CREAT|0666))==-1)
{
perror("shmget error\n");
exit(0);
}
sno=(int *)shmat(shmid,NULL,0);
sno[0]=0;
//-----------------------------------------------//

//-------------CREATE INET SOCKET----------------//
int sfd[3],nsfd,size;
struct sockaddr_in server,client;
size=sizeof(server);
int port=7009,i;
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

printf("SOCKET af_inet CREATED-waiting for connections\n");


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
printf("SOCKET af_unix CREATED\n");

        int rsfd;
	struct sockaddr_in dest,src;
	char packet[50];
	struct iphdr *ip = (struct iphdr *)packet;  

	if ((rsfd = socket(AF_INET, SOCK_RAW, IPPROTO_RAW)) < 0) {
		perror("error:");
		exit(EXIT_FAILURE);
	}

        dest.sin_family = AF_INET;
	dest.sin_port =0; 
	inet_pton(AF_INET,"127.0.0.1", (struct in_addr *)&dest.sin_addr.s_addr);
	memset(dest.sin_zero, 0, sizeof(dest.sin_zero));
	
	ip->ihl = 5;
	ip->version = 4;
	ip->tos = 0;
	ip->tot_len = htons(40);	/* 16 byte value */
	ip->frag_off = 0;		/* no fragment */
	ip->ttl = 64;			/* default value */
	ip->protocol =255;	/* protocol at L4 */
	ip->check = 0;			/* not needed in iphdr */
	ip->saddr = dest.sin_addr.s_addr;
	ip->daddr = dest.sin_addr.s_addr;
	

	
	
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


printf("now STARTED\n");
fd_set rfds;
struct timeval tv;
tv.tv_usec=0;tv.tv_sec=0;
int smax=0;


while(1)
{

    for(i=0;i<1;i++)
    {
        FD_SET(sfd[i],&rfds);
        smax=max(sfd[i],smax);
    }
    int retval=select(smax+1,&rfds,NULL,NULL,NULL);
    if(retval>0)
    {
        
        char *data=(char *)(packet+sizeof(struct iphdr));
        memset(data,'\0',sizeof(data));
        //data="TRAIN HAS ARRIVED";
        strcpy(data,"TRAIN HAS ARRIVED\n");
                      if (sendto(rsfd, (char *)packet, sizeof(packet), 0, 
			(struct sockaddr *)&dest, (socklen_t)sizeof(dest)) < 0)
			perror("packet1 send error:");
			perror("send to");
			printf("SOCKET:TRAIN ARRIVED MSG SNT\n");
			
    for(i=0;i<1;i++)
    {

        if(FD_ISSET(sfd[i],&rfds))
        {
       
            int j;
            for(j=0;j<3;j++)
            {
                if(flag[j]==0)break;
            }
            if(j<3)
            {
                
                flag[j]=1;
                nsfd=accept(sfd[i],(struct sockaddr *)&client,&size);
                printf("connection accepted %d \n",nsfd);
                int x=send_fd(connection_fd[j],nsfd);
                printf("hahahah %d\n", x);
                
                 memset(data,'\0',sizeof(data));
                // data="TRAIN HAS ARRIVED PLATFORM ";
                 strcpy(data,platname[j]);
                 
                
                  if (sendto(rsfd, (char *)packet, sizeof(packet), 0, 
			(struct sockaddr *)&dest, (socklen_t)sizeof(dest)) < 0)
			perror("packet1 send error:");
			printf("SOCKET:TRAIN ARRIVED PLATFORM MSG SNT\n");
                
            }
        }
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
