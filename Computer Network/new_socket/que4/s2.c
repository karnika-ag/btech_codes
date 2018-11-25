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
    struct sockaddr_un address;
    int  socket_fd, nbytes;
    char buffer[2000];


void rcvsfd(void *arg)
{
int no=*(int *)arg;
int n;
char buf[2000];
fd_set rfds;
struct timeval tv;
tv.tv_usec=0;tv.tv_sec=0;
printf("s2: thr %d created\n",no);
while(1)
{
   if(flag[no]==1)
   {
      printf("s2: entered thr %d \n",no);
      flag[no]=0;
      while(1)
      {
      FD_SET(socket_fd,&rfds);
      int ret=select(socket_fd+1,&rfds,NULL,NULL,(struct timeval *)&tv);
      if(ret>=0 && FD_ISSET(socket_fd,&rfds))
      {
      printf("s2 : accepted in thr %d\n",no);
      int nsfd=recv_fd(socket_fd);
      flag[no+1]=1;
      printf("connection accepted in s2 thr %d\n",no);
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
      break;
      }
      }
   }
}
exit(0);
}

int main()
{


//------------CONNECT TO UNIX SOCKET--------------------//
    socket_fd = socket(PF_UNIX, SOCK_STREAM, 0);
    if(socket_fd < 0)
    {
        printf("socket() failed\n");
        return 1;
    }
    memset(&address, 0, sizeof(struct sockaddr_un));
    address.sun_family = AF_UNIX;
    snprintf(address.sun_path,sizeof(address.sun_path), "./demo_socket0");
    connect(socket_fd, (struct sockaddr *) &address, sizeof(struct sockaddr_un));
    perror("connect");
//------------------------------------------------------------------//

int count=read(socket_fd,buffer,sizeof(buffer));
buffer[count]='\0';
write(1,buffer,strlen(buffer));

printf("STARTED: WAITING TO RCV NSFD\n");

flag[0]=1;
pthread_t thr[5];
int val[4]={0,1,2,3};
int i;
int retval;
for(i=0;i<4;i++)
{
printf("s2: thread %d creating\n",i);
if((retval=pthread_create(&thr[i],NULL,(void *)&rcvsfd,(void *)&val[i]))==-1)
{
perror("pthread");
printf("error in creating thread\n");
}
}


 for(i=0;i<4;i++)
 pthread_join(thr[i],NULL);
 
  return 0;
}
