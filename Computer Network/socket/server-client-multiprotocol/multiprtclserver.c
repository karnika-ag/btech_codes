#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<sys/select.h>
fd_set rfds;
struct timeval tv;
int csfd,lsfd,nsfd,size;
socklen_t frmlen;
struct sockaddr_in server,from,client;
char buf[2000];
char *msg;
char *fun1()
{
int i;
for(i=0;i<strlen(buf);i++)
{
  if(buf[i]>=97 && buf[i]<=122)
  {
    buf[i]=buf[i]-32;
  }
}

return buf;
}

int max(int a,int b)
{
return ((a>b)?a:b);
}
int main()
{
  int frmlen,rc;
   frmlen=sizeof(server);
   server.sin_family=AF_INET;
   server.sin_addr.s_addr=INADDR_ANY;
   server.sin_port=htons(8888);
   
  //-------------------------------------------------------------------//
  lsfd=socket(AF_INET,SOCK_DGRAM,0);
  if(lsfd<0)
  {
  printf("udp socket error\n");
  exit(0);
  }
  
   rc=bind(lsfd,(struct sockaddr *)&server,sizeof(server));
   if(rc<0)
   {
   printf("udp bind error\n");
   exit(0);
   }

  
  csfd=socket(AF_INET,SOCK_STREAM,0);
  if(csfd<0)
  {
  printf("tcp socket error\n");
  exit(0);
  }
 
   rc=bind(csfd,(struct sockaddr *)&server,sizeof(server));
   if(rc<0)
   {
   printf("tcp bind error\n");
   exit(0);
   }
   
     listen(csfd,6); 
     
   //---------------------------------------------------------//  
     
     int n=0,rval;
     tv.tv_usec=0;tv.tv_sec=0; 
    
     
    while(1)
    {
     n=0;
     FD_SET(csfd,&rfds);
     n=max(n,csfd);
     FD_SET(lsfd,&rfds);
     n=max(n,lsfd);
     
     rval=select(n+1,&rfds,NULL,NULL,(struct timeval *)&tv);
     
	if (rval < 0) 
	{
		    perror ("select()");
		    exit (1);
	}

  if(FD_ISSET(csfd,&rfds))
  {
     
      nsfd=accept(csfd,(struct sockaddr *)&client,&size);
      rc=recv(nsfd,buf,sizeof(buf),0);
      buf[rc]='\0';
      printf("TCP SERVER:%d bytes message from CLIENT : %s \n",rc,buf);
      
      char *str=fun1(buf);
      
      write(nsfd,buf,strlen(buf));
     
     
  }
  else if( FD_ISSET(lsfd,&rfds))
  {
   memset(&from,'0',sizeof(from));
   rc = recvfrom(lsfd,buf,2000,0,(struct sockaddr *)&from,&frmlen);
       if (rc < 0)
       {
       printf("recv error\n");
       exit(0);
       }
           buf[rc]='\0';
          printf("UDP SERVER:%d bytes message from CLIENT : %s \n",rc,buf);
   rc = sendto(lsfd,"RECEIVED MSG FROM U\n",19,0,(struct sockaddr *)&from,frmlen);
       if (rc < 0)
       {
       printf("send error\n");  
       }

  }


} 
     
      
}
