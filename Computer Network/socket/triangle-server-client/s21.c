#include<stdio.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<string.h>
#include<stdlib.h>
#include<error.h>
int sfd,sfd1;
void fun1()
{
   char str[BUFSIZ];
   while(1)
   {
   printf("CLIENT : enter msg \n");
     gets(str);
   write(sfd1, str, strlen(str));
   perror("write:\n");
   }
   exit(0);
 
}

void fun2()
{
   char str[BUFSIZ];
  while(1)
   {
   int n=read(sfd1,str,sizeof(str));
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

s2.sin_family=AF_INET;
s2.sin_port=htons(8566);
s2.sin_addr.s_addr=INADDR_ANY;
rc=bind(sfd,(struct sockaddr *)&s2,sizeof(s2));
if(rc<0)
{
printf("bind not create \n");
exit(0);
}

listen(sfd,2);

nsfd=accept(sfd,(struct sockaddr *)&s1,&size);
if(nsfd>0)
{
  printf("connection accepted\n");
  memset(&c1,'0',sizeof(c1));
  rc=recv(nsfd,(struct sockaddr *)&c1,sizeof(c1),0);
  if(rc<0)
  {
  printf("receive nt proper connect error\n");
  exit(0);
  }
  printf("msg received\n");
  
  //----------------------------------------------------//
  //socklen_t namelen = sizeof(c1);
  //int err = getsockname(nsfd, (struct sockaddr*) &c1, &namelen);
         
    char buffer[100];
    const char* p = inet_ntop(AF_INET, &c1.sin_addr, buffer, 100);
   printf("local port: %d\n", (int) ntohs(c1.sin_port));        
    if(p != NULL)
    {
        printf("Local ip is : %s \n" , buffer);
    } 
  
  
  //-------------------------------------------------------//
  
  sleep(100);
  sfd1=socket(AF_INET,SOCK_STREAM,0);
  //c1.sin_port=htons(8456);
  rc=connect(sfd1,(struct sockaddr *)&c1,sizeof(c1));
  if(rc<0)
  {
  printf("connect error\n");
  exit(0);
  }
  else
  {
   printf("connected to c1\n");        
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


