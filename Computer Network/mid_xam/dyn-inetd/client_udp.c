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

void fun1()
{
   char str[BUFSIZ];
   while(1)
   {
   printf("CLIENT : enter msg \n");
   memset(str,'\0',sizeof(str));
   fgets(str,BUFSIZ,stdin);
   int n=sendto(sfd,str,strlen(str),0,(const struct sockaddr *)&server,len);
   if (n < 0) error("Sendto");
   }
   exit(0);
 
}

void fun2()
{
   char str[BUFSIZ];
   size=sizeof(struct sockaddr_in);
  while(1)
   {
   int n = recvfrom(sfd,str,BUFSIZ,0,(struct sockaddr *)&from, &size);
   if (n < 0) error("recvfrom");
   str[n]='\0';
   printf("CLIENT : received from server:- %s\n",str);
   }
  exit(0);
}

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
      
pthread_t thr[2];
 
   if((rc=pthread_create(&thr[0],NULL,(void *)&fun1,NULL))==-1)
   {
   perror("pthread create error\n");
   exit(0);
   }
   if((rc=pthread_create(&thr[1],NULL,(void *)&fun2,NULL))==-1)
   {
   perror("pthread create error\n");
   exit(0);
   }
   
   pthread_join(thr[0],NULL);
   pthread_join(thr[1],NULL);   
   
   
close(sfd);


}
