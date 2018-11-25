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
int max(int a,int b)
{
if(a>b)return a;
return b;
}


int csfd;
char *myfifo1="ctos_fifo2";

int main(int argc,char *argv[])
{

//-----------CREATING PIPES-----------//

   mkfifo(myfifo1,0666);
   csfd= open(myfifo1, O_RDWR);
   printf("pipe2 created\n");

//------------------------------//

//------------CONNECT TO UNIX SOCKET--------------------//
    struct sockaddr_un address;
    int  socket_fd, nbytes;
    char buffer[2000];
    socket_fd = socket(PF_UNIX, SOCK_STREAM, 0);
    if(socket_fd < 0)
    {
        printf("socket() failed\n");
        return 1;
    }
    memset(&address, 0, sizeof(struct sockaddr_un));
    address.sun_family = AF_UNIX;
    snprintf(address.sun_path,sizeof(address.sun_path), "./demo_socket2");
    connect(socket_fd, (struct sockaddr *) &address, sizeof(struct sockaddr_un));
    perror("connect");
//------------------------------------------------------------------//

    
    printf("gets connected to main server\n");
    read(socket_fd,buffer,sizeof(buffer));
    write(1,buffer,strlen(buffer));
   printf("everythng okkk\n");
   fd_set rfds;
   struct timeval tv;
   tv.tv_usec=0;tv.tv_sec=0;
   FD_SET(socket_fd,&rfds);
   static int no=-1;
   int nsfd[9];
   int smax=0;
   int flag=0,i;
   
   while(1)
   {
   FD_SET(socket_fd,&rfds);
   smax=max(smax,socket_fd);
   flag=0;
   int ret= select(smax+1,&rfds,NULL,NULL,(struct timeval *)&tv);
   if(ret>=0)
   {
    if(FD_ISSET(socket_fd,&rfds))
    {
    no++;
    printf("NEW CLIENT %d in s3\n",no);
    nsfd[no]=recv_fd(socket_fd);
    printf("nsfd = %d\n",nsfd[no] );
    FD_SET(nsfd[no],&rfds);
    smax=max(smax,nsfd[no]);
    flag=1;
    write(nsfd[no],"i m assigned to u ..lets talk\n",strlen("i m assigned to u ..lets talk\n"));
    write(nsfd[no],"i'll repeat whatever u send\n",strlen("i'll repeat whatever u send\n"));

    }
    if(flag==0)
    for(i=0;i<=no;i++)
    {
       if(FD_ISSET(nsfd[i],&rfds))
       {
           int n=read(nsfd[i],buffer,sizeof(buffer));
           buffer[n]='\0';
           printf("s3: recv msg : client %d : %s\n",i,buffer);        
           write(nsfd[i],buffer,strlen(buffer));    
           buffer[n]='0'+no;
           buffer[n+1]='\0';
           write(csfd,buffer,strlen(buffer));
       }
       FD_SET(nsfd[i],&rfds);
    }
   }
   
  
  }
    
 
    return 0;
}
