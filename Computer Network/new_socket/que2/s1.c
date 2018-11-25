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
int fd;


void fun2(void *arg)
{
int n;
   int sfd=*(int *)arg;
   char buf[BUFSIZ];
write(sfd,"i m assigned to u ..lets talk\n",strlen("i m assigned to u ..lets talk\n"));
write(sfd,"i'll repeat whatever u send\n",strlen("i'll repeat whatever u send\n"));
while((n=recv(sfd,buf,sizeof(buf),0))>0)
{
buf[n]='\0';
write(1,buf,strlen(buf));
write(sfd,buf,strlen(buf));
}
exit(0);

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
int *sno;
int ppid;
void fun(int signo)
{
printf("exiting\n");
sno[0]=0;
kill(ppid,SIGUSR1);
exit(0);
}

int main(int argc,char *argv[])
{
signal(SIGALRM,fun);
int shmid;

key_t key=ftok(".",'a');
if((shmid=shmget(key,sizeof(int),IPC_CREAT|0666))==-1)
{
perror("shmget error\n");
exit(0);
}
sno=(int *)shmat(shmid,NULL,0);
ppid=atoi(argv[1]);

    struct sockaddr_un address;
    int  socket_fd, nbytes;
    char buffer[256];

    socket_fd = socket(PF_UNIX, SOCK_STREAM, 0);
    if(socket_fd < 0)
    {
        printf("socket() failed\n");
        return 1;
    }

    /* start with a clean address structure */
    memset(&address, 0, sizeof(struct sockaddr_un));
    address.sun_family = AF_UNIX;
    snprintf(address.sun_path,sizeof(address.sun_path), "./demo_socket0");
    connect(socket_fd, (struct sockaddr *) &address, sizeof(struct sockaddr_un));
    perror("connect");
    
    printf("gets connected to main server\n");
    //read(socket_fd,buffer,sizeof(buffer));
   // write(1,buffer,strlen(buffer));
   printf("everythng okkk\n");
   fd_set rfds;
   struct timeval tv;
   tv.tv_usec=0;tv.tv_sec=0;
   FD_SET(socket_fd,&rfds);
   
   alarm(100);
   while(1)
   {
    int ret= select(socket_fd+1,&rfds,NULL,NULL,(struct timeval *)&tv);
    printf("Somethng got selected\n");
    
    int fd=recv_fd(socket_fd);
    printf("fd = %d\n",fd );
  
     pthread_t thr;
    int rc;
   if(((rc=pthread_create(&thr,NULL,(void *)&fun2,(void *)&fd))==-1))
   {
   perror("pthread create error\n");
   exit(0);
   }
   
   FD_SET(socket_fd,&rfds);
   
   }
   
    
   //pthread_join(thr,NULL);
    
    //}
    
    return 0;
}
