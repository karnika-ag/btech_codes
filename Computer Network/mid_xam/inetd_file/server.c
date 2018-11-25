#include<stdio.h>
#include<string.h>  
#include<stdlib.h>  
#include<sys/socket.h>
#include<arpa/inet.h>
#include<unistd.h>   
#include<pthread.h>
#include<sys/select.h>
#include<math.h>
#include<semaphore.h>
#include<signal.h>
struct inetd
{
int n,p,port,exin,limit,s,w;
}; 
//p-protocol s-process/thread/fuction
//0-tcp 1-udp 0-ext 1-int 0-process 1-thread 2-function 0-wait 1-nowait
int max(int a,int b)
{
if(a>b)return a;
else return b;
}
int count1=3,count2=2,count3,count4=1;
sem_t sem1,sem2,sem3,sem4;
pthread_t thr[15];
int arr[15];
int sfd[6];

void fun2(void *arg)
{
int nsfd=*(int *)arg;
int i,num=0,n;
char *buf,msg[2000];
buf="i m assigned to u ..lets talk\n";
write(nsfd,buf,strlen(buf));
buf="i'll repeat whatever u send\n";
write(nsfd,buf,strlen(buf));
while((n=recv(nsfd,msg,sizeof(msg),0))>0)
{
msg[n]='\0';
write(1,msg,strlen(msg));
write(nsfd,msg,strlen(msg));
num++;
if(num==5)
break;
}
close(nsfd);
sem_wait(&sem2);
count2++;
sem_post(&sem2);
}

void fun1()
{
sem_wait(&sem1);
count1++;
sem_post(&sem1);
signal(SIGUSR1,fun1);
}


void fun3()
{
  int rc;
  socklen_t frmlen;
  struct sockaddr_in server,from;
  frmlen = sizeof(struct sockaddr_in);
  sem_wait(&sem3);
       char buf[2000];
       memset(&buf,'\0',sizeof(buf));
       rc = recvfrom(sfd[2],buf,2000,0,(struct sockaddr *)&from,&frmlen);
       if (rc < 0)
       {
       printf("recv error\n");
       exit(0);
       }
       rc = sendto(sfd[2],buf,strlen(buf),0,(struct sockaddr *)&from,frmlen);
       if (rc < 0)
       {
       printf("send error\n");
       exit(0);
       }
  sem_post(&sem3);     
}

void fun5()
{
sem_wait(&sem4);
count4=1;
sem_post(&sem4);
signal(SIGUSR2,fun5);
}

int main()
{
signal(SIGUSR1,fun1);
signal(SIGUSR2,fun5);
int nsfd,pid;
int i;
int val;
//------------------READ FILE-----------------------------------------//
struct inetd file[5];
file[0].n=1;file[0].p=0;file[0].port=7011;file[0].exin=0;file[0].limit=25;file[0].s=0;file[0].w=0;
file[1].n=2;file[1].p=0;file[1].port=7022;file[1].exin=1;file[1].limit=15;file[1].s=1;file[1].w=0;
file[2].n=3;file[2].p=1;file[2].port=7033;file[2].exin=1;file[2].limit=0;file[2].s=2;file[2].w=0;
file[3].n=4;file[3].p=0;file[3].port=7044;file[3].exin=0;file[3].limit=0;file[3].s=0;file[3].w=0;
file[4].n=5;file[4].p=1;file[4].port=7055;file[4].exin=0;file[4].limit=0;file[4].s=0;file[4].w=1;
//---------------------------------------------------------------------//

sem_init(&sem1,0,1);
sem_init(&sem2,0,1);
sem_init(&sem3,0,1);
sem_init(&sem4,0,1);
int rc;
struct sockaddr_in server,client;
socklen_t len;
len=sizeof(server);
for(i=0;i<5;i++)
{
  if(file[i].p==0)
  {
  sfd[i]=socket(AF_INET,SOCK_STREAM,0);
        if(sfd[i]==-1)
	{
	printf("could not create socket\n");
	exit(0);
	}
	
   len=sizeof(server);
   server.sin_family=AF_INET;
   server.sin_addr.s_addr=INADDR_ANY;
   server.sin_port=htons(file[i].port);
   rc=bind(sfd[i],(struct sockaddr *)&server,sizeof(server));
   if(rc<0){printf("bind failed\n");exit(0);} 	
   listen(sfd[i],5);
  }
  else if(file[i].p==1)
  {
  sfd[i]=socket(AF_INET,SOCK_DGRAM,0);
        if(sfd[i]==-1)
	{
	printf("could not create socket\n");
	exit(0);
	}
   len=sizeof(server);
   server.sin_family=AF_INET;
   server.sin_addr.s_addr=INADDR_ANY;
   server.sin_port=htons(file[i].port);
   rc=bind(sfd[i],(struct sockaddr *)&server,sizeof(server));
   if(rc<0){printf("bind failed\n");exit(0);} 	 	
  }
}

fd_set rfds;
struct timeval tv;
tv.tv_usec=0;tv.tv_sec=0;
int n=0,rval;
printf("SERVER STARTED  %d\n",getpid());
while(1)
{

for(i=0;i<5;i++)
{
FD_SET(sfd[i],&rfds);
n=max(n,sfd[i]);
}

rval=select(n+1,&rfds,NULL,NULL,(struct timeval *)&tv);
if(rval>0)
{
  if(FD_ISSET(sfd[0],&rfds))
  {
     printf("came in s1\n");
     sem_wait(&sem1);
     if(count1>0)
     {
     count1--;
     sem_post(&sem1);
     int nsfd=accept(sfd[0],(struct sockaddr *)&client,&len);
     pid=fork();
     if(pid==0)
     {
        close(sfd[0]);close(sfd[1]);close(sfd[2]);close(sfd[3]);close(sfd[4]);
        dup2(nsfd,0);
        char param[2];
        int ppid=getppid();
        sprintf(param,"%d",ppid);
        //execv("abc",0);
        execl("abc","s1",param,(char *)0);
        printf("assigned to someone else\n");
     }
     }
     else
     {
     printf("in the waiting list\n");
     sem_post(&sem1);
     }
  }
  if(FD_ISSET(sfd[1],&rfds))
  {
     printf("came in s2\n");
     sem_wait(&sem2);
     if(count2>0)
     {
     count2--;
     int nsfd=accept(sfd[1],(struct sockaddr *)&client,&len);
     arr[count2]=nsfd;
     int po=count2;
     sem_post(&sem2);
     pthread_create(&thr[po],NULL,(void *)&fun2,(void *)&arr[po]);

     }
     else
     {
     printf("in the waiting list\n");
     sem_post(&sem2);
     }    
  }
  if(FD_ISSET(sfd[2],&rfds))
  {
     printf("came in s3\n");
     fun3();
     printf("fun3() called\n");
     
  }
  if(FD_ISSET(sfd[3],&rfds))
  {
     printf("came in s4\n");
     int nsfd=accept(sfd[3],(struct sockaddr *)&client,&len);
     printf("accepted in s4\n");
     pid=fork();
     if(pid==0)
     {
        close(sfd[0]);close(sfd[1]);close(sfd[2]);close(sfd[3]);close(sfd[4]);
        dup2(nsfd,0);
        printf("going to exec\n");
        execv("abd",0);
        //execl("abc","s1",param,(char *)0);
        printf("assigned to someone else\n");
     }
     else if(pid>0)
     {
     close(nsfd);
     }
     
  }
  if(FD_ISSET(sfd[4],&rfds))
  {
      printf("came in s5\n");
      sem_wait(&sem4);
      if(count4>0)
      {
      count4--;
      sem_post(&sem4);
      int pid=fork();
      if(pid==0)
      {
         dup2(sfd[4],0);
         close(sfd[0]);close(sfd[1]);close(sfd[2]);close(sfd[3]);close(sfd[4]);
         char param[2];
         int ppid=getppid();
         sprintf(param,"%d",ppid);
         execl("abe","s5",param,(char *)0);         
         
      }  
      }
      else
      {
      printf("waiting in s4\n");
      sem_post(&sem4);
      }
  }
}
}

return 0;
}

