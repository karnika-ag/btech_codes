#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <string.h>
#include <netdb.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <netinet/udp.h>
#include <string.h>
int rc,sfd,nsfd;

//socklen_t len;
int store[][8]={{2,12,11,5,1,10,15,13},{8,9,4,14,3,7,6,16}};
int main(int argc,char *argv[])
{
struct sockaddr_in src,dest;
socklen_t len=sizeof(dest);
int i,cnt=0;
sfd=socket(AF_INET,SOCK_STREAM,0);
perror("sfd");
src.sin_family=AF_INET;
src.sin_port=htons(atoi(argv[1]));
inet_pton(AF_INET,"127.0.0.1",(struct in_addr *)&src.sin_addr);
perror("inet");
rc=bind(sfd,(struct sockaddr *)&src,sizeof(src));
perror("bind");
listen(sfd,3);
perror("listen");
char buffer[20];
while((nsfd=accept(sfd,(struct sockaddr *)&dest,(socklen_t *)&len))>0)
{
perror("accept");
for(i=0;i<8;i++)
{
 sprintf(buffer,"%d",store[cnt][i]);
 printf("%s\n",buffer);
 write(nsfd,buffer,strlen(buffer));
 perror("write");
 sleep(1);
}
cnt++;
if(cnt==2)
break;
}

int pid=fork();
if(pid==0)
{
printf("child created\n");
execv("jud",0);
}
else if(pid>0)
{
wait(&pid);
printf("child is over\n");
}
printf("DISTRIBUTOR WORK DONE\n");
}


