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
void fun1()
{
   char str[BUFSIZ];
   while(1)
   {
   printf("CLIENT : enter msg \n");
//   scanf("%s", str);
     gets(str);
 //    str[strlen(str)]='\0';
   write(sfd, str, strlen(str));
   perror("write:\n");
   }
   exit(0);
 
}

void fun2()
{
   char str[BUFSIZ];
   int n=read(sfd,str,sizeof(str));
   str[n]='\0';
   perror("Read:\n"); 
   printf("CLIENT : received from server:- %s\n",str);
   pthread_t thr;
   int rc;
   if((rc=pthread_create(&thr,NULL,(void *)&fun1,NULL))==-1)
   {
   perror("pthread create error\n");
   exit(0);
   }  
  while(1)
   {
   n=read(sfd,str,sizeof(str));
   str[n]='\0';
   perror("Read:\n"); 
   printf("CLIENT : received from server:- %s\n",str);
   }
  exit(0);
}

int main(int argc, char *argv[])
{
int n;
char smsg[2000],rmsg[2000];
struct sockaddr_in server;
if(argc!=3)
{
printf("give ip &port of server\n");
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
server.sin_port=htons(atoi(argv[2]));
int rc=inet_pton(AF_INET,argv[1],&server.sin_addr);
if(rc<=0)
{
printf("inet pton error\n");
exit(0);
}
rc=connect(sfd,(struct sockaddr_in *)&server,sizeof(server));
if(rc<0)
{
printf("connect error\n");
exit(0);
}
      
      
pthread_t thr[2];
 
   if((rc=pthread_create(&thr[0],NULL,(void *)&fun2,NULL))==-1)
   {
   perror("pthread create error\n");
   exit(0);
   }
 /*  if((rc=pthread_create(&thr[1],NULL,(void *)&fun2,NULL))==-1)
   {
   perror("pthread create error\n");
   exit(0);
   }
 */  
   pthread_join(thr[0],NULL);
 //  pthread_join(thr[1],NULL);   
   
   
         
 

return 0;
}
