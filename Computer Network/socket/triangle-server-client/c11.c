#include <sys/socket.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <arpa/inet.h> 
#include<stdlib.h>
int sfd,nsfd,sfd1;
void fun1()
{
   char str[BUFSIZ];
   while(1)
   {
   printf("CLIENT : enter msg \n");
     gets(str);
   write(nsfd, str, strlen(str));
   perror("write:\n");
   }
   exit(0);
 
}

void fun2()
{
   char str[BUFSIZ];
  while(1)
   {
   int n=read(nsfd,str,sizeof(str));
   str[n]='\0';
   perror("Read:\n"); 
   printf("CLIENT : received from server:- %s\n",str);
   }
  exit(0);
}

int main(int argc, char *argv[])
{
int n,size,rc;
char smsg[2000],rmsg[2000];
struct sockaddr_in server,c1,s2;
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
rc=inet_pton(AF_INET,argv[1],&server.sin_addr);


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


else
{
 printf("connected to s1\n");

 
 sfd1=socket(AF_INET,SOCK_STREAM,0);
       if(sfd1<0)
	{
	printf("socket not created\n");
	exit(0);
	}

 c1.sin_family=AF_INET;
 c1.sin_addr.s_addr=INADDR_ANY;
 c1.sin_port=htons(8456);     
 rc=bind(sfd1,(struct sockaddr *)&c1,sizeof(c1));
 if(rc<0)
 {
 printf("bind failed\n");
 exit(0);
 }
 listen(sfd1,2);
 
 memset(&s2,'0',sizeof(s2));
 nsfd=accept(sfd1,(struct sockaddr *)&s2,&size);
 printf("everything done\n");
 if(nsfd>0)
 {
   printf("now chat with s2\n");    
           
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
   
   
 
 }
 
 
}
return 0;
}
