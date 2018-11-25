#include <sys/types.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <netdb.h>
#include <stdio.h>
#include<signal.h>
int main(int argc,char *argv[])
{
   int ppid=atoi(argv[1]);
   printf("%s  %d\n",argv[0],ppid);
   int sfd,rc;
   sfd=dup(0);
   socklen_t frmlen;
   struct sockaddr_in from,client;
   char buf[2000];
   frmlen = sizeof(struct sockaddr_in);
   int num=0,flag=1;
   while (1) 
   {
      flag=1;
       memset(&from,'0',sizeof(from));
       rc = recvfrom(sfd,buf,2000,0,(struct sockaddr *)&from,&frmlen);
       if (rc < 0)
       {
       printf("recv error\n");
       exit(0);
       }
       buf[rc]='\0';
       if(num==0)
       {
       memcpy(&client, &from, sizeof(struct sockaddr_in));
       }
       else
       {
          if((memcmp(&client,&from,sizeof(struct sockaddr_in)))==0)
          {
            flag=1;
          }
          else
          {
          flag=0;
          }
       }
       if(flag==1)
       {
       printf("Received a msg from client : %s\n",buf);
       rc = sendto(sfd,buf,strlen(buf),0,(struct sockaddr *)&client,frmlen);
       if (rc < 0)
       {
       printf("send error\n");
       exit(0);
       }
       num++;
       if(num==5)
       break;
       }
    }
  close(sfd);
  kill(ppid,SIGUSR2);   
    
}
