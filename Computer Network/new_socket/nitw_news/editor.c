#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <netdb.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <arpa/inet.h> 

int max(int a,int b)
{
if(a>b)return a;
return b;
}

int main()
{
char buf[2000];
int n=0,i;
int fd[5];
char obj[]="./read1";
for(i=1;i<=2;i++)
{
obj[6]=i+'0';
FILE *filed=popen(obj,"r");
fd[i-1]=fileno(filed);
}


int sfd[3],size;
struct sockaddr_in server,client;
size=sizeof(server);
int port=7000,rc;

for(i=0;i<1;i++)
{
sfd[i]=socket(AF_INET,SOCK_STREAM,0);
if(sfd[i]==-1)
{
printf("could not create socket\n");
exit(0);
}
char add[]="127.0.0.1";
server.sin_family=AF_INET;
server.sin_port=htons(port+i);
rc=inet_pton(AF_INET,add,&server.sin_addr);
if(rc<=0)
{
printf("inet pton error\n");
exit(0);
}
rc=connect(sfd[i],(struct sockaddr *)&server,sizeof(server));
perror("connect inet");
}



fd_set rfds;
struct timeval tv;
tv.tv_usec=0;tv.tv_sec=0;
int smax=0;

while(1)
{

    for(i=0;i<2;i++)
    {
        FD_SET(fd[i],&rfds);
        smax=max(fd[i],smax);
    }
    int retval=select(smax+1,&rfds,NULL,NULL,NULL);
     if(retval>0)
     {
       
        for(i=0;i<2;i++)
        {
           if(FD_ISSET(fd[i],&rfds))
           {
               int n=read(fd[i],buf,sizeof(buf));
               buf[n]='\0';
               write(1,buf,strlen(buf));
               write(sfd[0],buf,strlen(buf));
           }    
        }
     } 
}
}
