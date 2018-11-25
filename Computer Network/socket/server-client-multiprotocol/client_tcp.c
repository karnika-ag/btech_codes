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

int sfd;


int main(int argc, char *argv[])
{
int n;
char buf[2000];
struct sockaddr_in server;
if(argc!=2)
{
printf("give ip of server\n");
exit(0);
}
sfd=socket(AF_INET,SOCK_STREAM,0);
if(sfd<0)
{
printf("socket not created\n");
exit(0);
}

memset(&server, '0', sizeof(server));
server.sin_family=AF_INET;
server.sin_port=htons(8888);
int rc=inet_pton(AF_INET,argv[1],&server.sin_addr);
if(rc<=0)
{
printf("inet pton error\n");
exit(0);
}
rc=connect(sfd,(struct sockaddr *)&server,sizeof(server));
if(rc<0)
{
printf("connect error\n");
exit(0);
}





 printf("CLIENT : enter msg \n");
 fgets(buf,2000,stdin);
 write(sfd, buf, strlen(buf));
 perror("write:\n");
 n=read(sfd,buf,sizeof(buf));
 buf[n]='\0';
 perror("Read:\n"); 
 printf("CLIENT : received from server:- %s\n",buf);
 








      
   
return 0;
}
