#include<stdio.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<string.h>
#include<stdlib.h>
#include<error.h>
int sfd;
void fun1()
{
   char str[BUFSIZ];
   while(1)
   {
   printf("CLIENT : enter msg \n");
     gets(str);
   write(sfd, str, strlen(str));
   perror("write:\n");
   }
   exit(0);
 
}

void fun2()
{
   char str[BUFSIZ];
  while(1)
   {
   int n=read(sfd,str,sizeof(str));
   str[n]='\0';
   perror("Read:\n"); 
   printf("CLIENT : received from server:- %s\n",str);
   }
  exit(0);
}


int main()
{
int nsfd,rc,size;
struct sockaddr_in s1,s2,c1;
sfd=socket(AF_INET,SOCK_STREAM,0);
if(sfd==-1)
{
printf("could not create socket\n");
exit(0);
}

s1.sin_family=AF_INET;
s1.sin_port=htons(8888);
s1.sin_addr.s_addr=INADDR_ANY;
rc=bind(sfd,(struct sockaddr *)&s1,sizeof(s1));
if(rc<0)
{
printf("bind not create \n");
exit(0);
}

listen(sfd,2);

nsfd=accept(sfd,(struct sockaddr *)&c1,&size);
if(nsfd>0)
{

  rc=recv(nsfd,(struct sockaddr *)&c1,sizeof(c1),0))
  if(rc>0)
  {
  
  
  }
  
  rc=connect(sfd,(struct sockaddr *)&c1,sizeof(c1));
  if(rc<0)
  {
  printf("connect error\n");
  exit(0);
  }
  else
  {
              
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
close(nsfd);

}


