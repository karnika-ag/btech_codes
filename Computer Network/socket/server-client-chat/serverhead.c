#include<stdio.h>
#include<string.h>  
#include<stdlib.h>  
#include<sys/socket.h>
#include<arpa/inet.h>
#include<unistd.h>   
#include<pthread.h>
#include<sys/select.h>
fd_set rfds;
struct timeval tv;
int max(int a,int b)
{
if(a>b)return a;
else return b;
}
int main()
{
int sfd,nsfd[15],size,cur_in;
char *buf;
cur_in=dup(0);
struct sockaddr_in server,client;
sfd=socket(AF_INET,SOCK_STREAM,0);
if(sfd==-1)
{
printf("could not create socket\n");
exit(0);
}
server.sin_family=AF_INET;
server.sin_addr.s_addr=INADDR_ANY;
server.sin_port=htons(8888);
if(bind(sfd,(struct sockaddr *)&server,sizeof(server))<0)
{
printf("bind failed\n");
exit(0);
}
listen(sfd,3);

printf("SOCKET CREATED-waiting for connections\n");


int no=1,i,j,n=0,rval,len;
char msg[2000];
tv.tv_usec=0;tv.tv_sec=0;

//while(nsfd[no]=accept(sfd,(struct sockaddr_in *)&client,&size))
//{

//printf("connection accepted\n");
while(1)
{
FD_SET(sfd,&rfds);
n=max(n,sfd);
for(i=1;i<no;i++)
{
FD_SET(nsfd[i],&rfds);
n=max(n,nsfd[i]);
}
rval=select(n+1,&rfds,NULL,NULL,(struct timeval *)&tv);
if (rval < 0) 
{
            perror ("select()");
            exit (1);
}
else if(rval>0)
{ 
if(FD_ISSET(sfd,&rfds))
  {
      nsfd[no]=accept(sfd,(struct sockaddr *)&client,&size);
      no++;
      
  }  
else
{  
for(i=1;i<no;i++)
{
  
  if(FD_ISSET(nsfd[i],&rfds))
  {
      len=recv(nsfd[i],msg,sizeof(msg),0);
      
      msg[len]='\0';
      printf("SERVER:%d bytes message from CLIENT %d : %s \n",len,i,msg);
      
				for(j=1;j<no;j++)
				{
					if(j!=i)
					{
						write(nsfd[j],msg,strlen(msg));
					}    
				}   
  }
}
}
}
}
return 0;
}
