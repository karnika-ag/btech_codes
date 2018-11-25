#include<stdio.h>
#include<string.h>  
#include<stdlib.h>   
#include<sys/socket.h>
#include<arpa/inet.h> 
#include<unistd.h>   
#include <stdio.h>
#include <sys/types.h>
#include <dirent.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include<signal.h>
#include<sys/shm.h> 
#include<pthread.h> 
int main()
{
int nsfd=dup(0);
int size,n,num=0;
char *buf,msg[2000];
buf="i m assigned to u ..lets talk\n";
write(nsfd,buf,strlen(buf));
buf="i'll repeat whatever u send\n";
write(nsfd,buf,strlen(buf));
while((n=recv(nsfd,msg,sizeof(msg),0))>0)
{
msg[n]='\0';
write(1,msg,strlen(msg));
write(nsfd,msg,strlen(msg));
num++;
if(num==5)
break;
}
close(nsfd);
return 0;
} 
