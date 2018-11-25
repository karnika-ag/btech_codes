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
int sfd[3],nsfd,size;
struct sockaddr_in server,client;
int cur_out;

void fun1(int arg)
{
char buf[2000];
fd_set rfds;
struct timeval tv;
tv.tv_usec=0;tv.tv_sec=0;
int smax=0;

while(1)
{

FD_SET(nsfd,&rfds);
int retval=select(nsfd+1,&rfds,NULL,NULL,(struct timeval *)&tv);
if(retval>0 && FD_ISSET(nsfd,&rfds))
{
int n=read(nsfd,buf,sizeof(buf));
buf[n]='\0';
write(1,buf,strlen(buf));
}

}
exit(0);
}

int main()
{
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

nsfd=accept(sfd[0],(struct sockaddr *)&client,&size);
    
int pid=fork();
if(pid==0)
{
fun1(1);
}
else if(pid>0)    
{
fun1(2);
}


}
