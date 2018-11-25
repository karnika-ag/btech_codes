/* UDP client in the internet domain */
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

int sfd,len,size;
struct sockaddr_in server,from;


int main(int argc,char *argv[])
{
int size,n,rc;

char buf[2000];
if(argc!=3)
{
printf("give server ip and port\n");
exit(0);
}
sfd=socket(AF_INET,SOCK_DGRAM,0);
if(sfd<0)
{
printf("socket error\n");
exit(0);
}
server.sin_family=AF_INET;
server.sin_port=htons(atoi(argv[2]));
rc=inet_pton(AF_INET,argv[1],&server.sin_addr);
len=sizeof(struct sockaddr_in);

   printf("CLIENT : enter msg \n");
   memset(buf,'\0',sizeof(buf));
   fgets(buf,2000,stdin);
   n=sendto(sfd,buf,strlen(buf),0,(const struct sockaddr *)&server,len);
   if (n < 0)
   {
   printf("send error\n");
   exit(0);
   }
   n = recvfrom(sfd,buf,2000,0,(struct sockaddr *)&from, &size);
   if (n < 0) 
   {
   printf("recv error\n");
   exit(0);
   }
   buf[n]='\0';
   printf("CLIENT : received from server:- %s\n",buf);
  
   close(sfd);
}
