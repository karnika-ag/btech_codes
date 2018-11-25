#include <sys/types.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <netdb.h>
#include <stdio.h>

int main()
{
  int sfd,len,size,rc,n;
  socklen_t frmlen;
  struct sockaddr_in server,from,client[20];
  
  char buf[2000];
  sfd=socket(AF_INET,SOCK_DGRAM,0);
  if(sfd<0)
  {
  printf("socket error\n");
  exit(0);
  }
  len=sizeof(server);
   server.sin_family=AF_INET;
   server.sin_addr.s_addr=INADDR_ANY;
   server.sin_port=htons(8888);
   rc=bind(sfd,(struct sockaddr *)&server,sizeof(server));
   if(rc<0)
   {
   printf("bind error\n");
   exit(0);
   }
   frmlen = sizeof(struct sockaddr_in);
   int no=0,i,j;
   while (1) 
   {
       memset(&from,'0',sizeof(from));
       rc = recvfrom(sfd,buf,2000,0,(struct sockaddr *)&from,&frmlen);
       if (rc < 0)
       {
       printf("recv error\n");
       exit(0);
       }
      
       for(i=0;i<no;i++)
       {
//          if(client[i].sin_addr.s_addr == from.sin_addr.s_addr && client[no].sin_port==from.sin_port)
          if((memcmp(&client[i],&from,sizeof(struct sockaddr_in)))==0)
          {
          break;
          }
       }
       buf[rc]='\0';
       if(i==no)
       {
       memcpy(&client[no], &from, sizeof(struct sockaddr_in));
       no++;
       printf("NEW CLIENT CAME HURRAY\n");
       }
       printf("Received a msg from client %d : %s\n",i,buf);
       for(j=0;j<no;j++)
       {
      if(i!=j)
      {
       rc = sendto(sfd,buf,strlen(buf),0,(struct sockaddr *)&client[j],frmlen);
       if (rc < 0)
       {
       printf("send error\n");
       exit(0);
       }
       }
       }
   }
}
