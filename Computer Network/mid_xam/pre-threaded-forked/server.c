#include<stdio.h>
#include<string.h>  
#include<stdlib.h>  
#include<sys/socket.h>
#include<arpa/inet.h>
#include<unistd.h>   
#include<pthread.h>
#include<sys/select.h>

int max(int a,int b)
{
if(a>b)return a;
else return b;
}

void fun(void *arg)
{
int port=*(int *)arg;
printf("entered %d\n",port);
int nsfd[15];
struct sockaddr_in server,client;
int sfd=socket(AF_INET,SOCK_STREAM,0);
if(sfd==-1)
{
printf("could not create socket\n");
exit(0);
}
server.sin_family=AF_INET;
server.sin_addr.s_addr=INADDR_ANY;
server.sin_port=htons(port);

if(bind(sfd,(struct sockaddr *)&server,sizeof(server))<0)
{
printf("bind failed\n");
exit(0);
}
listen(sfd,3);
socklen_t size=sizeof(server);

fd_set rfds;
struct timeval tv;
int no=1,i,j,n=0,rval,len;
char msg[2000];
tv.tv_usec=0;tv.tv_sec=0;
printf("SOCKET READY %d\n",port);
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



exit(0);
}
int main()
{
pthread_t thr[52];
int arr[52];
int i,rc,pid,j;
for(i=1;i<=5;i++)
{
  pid=fork();
  if(pid==0)
  {
    for(j=1;j<=5;j++)
    {
        arr[(i-1)*5+j]=6000+10*i+j;
        printf("i m called %d\n",arr[(i-1)*5+j]);
        if((rc=pthread_create(&thr[(i-1)*5+j],NULL,(void *)&fun,(void *)&arr[(i-1)*5+j]))<0)
        {
           printf("error in pthread_create\n");
           exit(0);
        }
    }
    break;
  }
  else if(pid<0)
  {
    printf("not forked\n"); 
  }  
  else
  {
  printf("parent is here\n");
  }
}
for(i=1;i<=25;i++)
{
pthread_join(thr[i],NULL);
}
}
