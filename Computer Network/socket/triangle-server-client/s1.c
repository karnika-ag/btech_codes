#include<stdio.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<string.h>
#include<stdlib.h>
#include<error.h>
int main(int ar)
{
int sfd,nsfd,rc,size,sfd1;
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
memset(&c1,'0',sizeof(c1));
listen(sfd,2);
printf("started \n");
nsfd=accept(sfd,(struct sockaddr *)&c1,&size);
printf("getting conncered\n");
if(nsfd>0)
{
      char buffer[100];
      const char* p = inet_ntop(AF_INET, &c1.sin_addr, buffer, 100);
      printf("local port: %d\n", (int) ntohs(c1.sin_port));        
    if(p != NULL)
    {
        printf("Local ip is : %s \n" , buffer);
    } 



  memset(&s2,'0',sizeof(s2));
  s2.sin_family=AF_INET;
  s2.sin_port=htons(8566);
  //char *val="172.30.131.201";
//  char *val="172.30.128.144";
  char *val="127.0.0.1";
  rc=inet_pton(AF_INET,val,&s2.sin_addr);
  
    if(rc<=0)
    {
     printf("inet pton error\n");
     exit(0);
    }
  sfd1=socket(AF_INET,SOCK_STREAM,0);
  if(sfd1<0)
  {
  printf("socket with s2 error\n");
  }
  rc=connect(sfd1,(struct sockaddr *)&s2,sizeof(s2));
  if(rc<0)
  {
  printf("connect error\n");
  exit(0);
  }
  else
  {
    //write(sfd1,(void *)&s2,sizeof(s2));
   
     char buffer[100];
      const char* p = inet_ntop(AF_INET, &c1.sin_addr, buffer, 100);
      printf("local port: %d\n", (int) ntohs(c1.sin_port));        
    if(p != NULL)
    {
        printf("Local ip is : %s \n" , buffer);
    } 
  
   
    
       write(sfd1,(struct sockaddr*)&c1,sizeof(c1));
       perror("write:\n");
  }
}
//close(nsfd);

}


