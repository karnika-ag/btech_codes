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
int flag=0;

void fun(int signo)
{
flag=1;
}

int main()
{

signal(SIGUSR1,fun);
int sfd[5],nsfd[5]={-1},size;

printf("now s3 STARTED\n");
fd_set rfds;
struct timeval tv;
tv.tv_usec=0;tv.tv_sec=0;
int smax=0,num=0,i;
char buf[2000];


   for(i=0;i<5;i++)
    {
        FD_SET(i,&rfds);
        smax=max(i,smax);
    }
    

    
while(1)
{
    if(flag==1)
    break;  
    int retval=select(5,&rfds,NULL,NULL,NULL);
    if(retval>0)
    for(i=0;i<5;i++)
    {
      
		if(FD_ISSET(i,&rfds))
		{
		
		        int n=read(i,buf,sizeof(buf));
		        buf[n]='\0';
		        write(i,buf,strlen(buf));
		        FD_SET(i,&rfds);
		}
       	        FD_SET(i,&rfds);         
    }
    

}

printf("THIS s3 PROCESS IS EXITING\n");

int pid=fork();
if(pid==0)
{
char param[2];int u=2;
sprintf(param,"%d",u);
execl("s1","s1",param,(char *)0);
}
else if(pid>0)
{
for(i=0;i<5;i++)
{
if(i!=1)
close(i);
}
}


}
