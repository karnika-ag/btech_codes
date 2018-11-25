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

int max(int a,int b)
{
if(a>b)return a;
return b;
}



int main(int argc,char *argv[])
{
int sfd[5],nsfd[5]={-1},size;
int pno=atoi(argv[1]);
printf("pno = %d\n",pno);
struct sockaddr_in server,client;
size=sizeof(server);
int port=6000,i;

for(i=0;i<5;i++)
nsfd[i]=-1;

if(pno==1)
{
printf("creating sockets\n");
for(i=0;i<5;i++)
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


}

printf("now STARTED\n");
fd_set rfds;
struct timeval tv;
tv.tv_usec=0;tv.tv_sec=0;
int smax=0,num=0;
char buf[2000];

if(pno==1)
{
printf("came in\n");

   for(i=0;i<5;i++)
    {
       if(i!=1)
       {
        FD_SET(sfd[i],&rfds);
        smax=max(sfd[i],smax);
       }
    }
    

    
while(1)
{  
    
    int retval=select(smax+1,&rfds,NULL,NULL,NULL);
    if(retval>0)
    {
    for(i=0;i<5;i++)
    {   
        if(i!=1)
        if(nsfd[i]==-1)
        {
		if(FD_ISSET(sfd[i],&rfds))
		{
		
		        num++;
		        nsfd[i]=accept(sfd[i],(struct sockaddr *)&client,&size);
		        printf("connection accepted %d \n",nsfd[i]);
		        write(nsfd[i],"i m assigned to u ..lets talk\n",strlen("i m assigned to u ..lets talk\n"));
	 		if(num==4)
	 		break;           
		}
        }
        else
        {
		if(FD_ISSET(nsfd[i],&rfds))
		{
		        int n=read(nsfd[i],buf,sizeof(buf));
		        buf[n]='\0';
		        write(1,buf,strlen(buf));
		        write(nsfd[i],buf,strlen(buf));
		}
              
        
        }
    }
    smax=0;
    for(i=0;i<5;i++)
    {
     if(i!=1)
      if(nsfd[i]==-1)
      {
       FD_SET(sfd[i],&rfds);
       smax=max(sfd[i],smax);
      }
      else
      {
       FD_SET(nsfd[i],&rfds);
       smax=max(nsfd[i],smax);       
      }
    }
    
    }
    if(num==4)
    {
    break;
    }
}

printf("THIS PROCESS IS EXITING\n");

int pid=fork();
if(pid==0)
{
for(i=0;i<5;i++)
{
if(i!=1)
dup2(nsfd[i],i);
}
execv("s2",NULL);
}
else if(pid>0)
{
for(i=0;i<5;i++)
{
close(nsfd[i]);
}
sleep(30);
kill(pid,SIGUSR1);
}


}

if(pno!=1)
{

printf("FINNALLY CALLED AGAIN\n");

while(1)
{
for(i=0;i<5;i++)
if(i!=1)
FD_SET(i,&rfds);

    int retval=select(5,&rfds,NULL,NULL,NULL);
    if(retval>0)
    for(i=0;i<5;i++)
    {
                if(i!=1)
		if(FD_ISSET(i,&rfds))
		{
                        int n=read(i,buf,sizeof(buf));
		        buf[n]='\0';
		        write(i,buf,strlen(buf));
		        FD_SET(i,&rfds);		
		 
		}
        
     }


}

}
printf("to see what happen");
exit(0);
}
