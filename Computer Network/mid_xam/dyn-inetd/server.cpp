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
#include<fstream>
#include<iostream>
#include<sys/shm.h>
#include<sys/types.h>
#include<sys/ipc.h>
using namespace std;
struct inetd
{
int no;
char proto[20];
int port;
char inext[20];
int limit;
char serv[20];
char wait[20];
char file[20];
int count;
}; 

inetd store[100];
int sfd[20],count,smax=0,flag2=0;
struct sockaddr_in server,client;
socklen_t len;
fd_set rfds;
struct timeval tv;
int *sno;
int shmid;
sem_t sem3;

void modify()
{
  struct inetd temp;
  int i=0,flag=0;
  int check[50]={0};
  ifstream fin;
  fin.open("inetd_config.txt");
  while(!fin.eof())
  {
        flag=0;
        if(i<count)
        {
	fin>>temp.no;
	fin>>temp.proto;
	if((strcmp(temp.proto,store[i].proto))!=0)
	{
	strcpy(store[i].proto,temp.proto);
	flag=1;
	}
	fin>>temp.port;
	if(temp.port!=store[i].port)
	{
	flag=1;
	store[i].port=temp.port;
	}	
	fin>>temp.inext;
	if((strcmp(temp.inext,store[i].inext))!=0)
	{
	strcpy(store[i].inext,temp.inext);
	}
	fin>>temp.limit;
	if(temp.limit!=store[i].limit)
	{
	store[i].limit=temp.limit;
	}	
	fin>>temp.serv;
	if((strcmp(temp.serv,store[i].serv))!=0)
	{
	strcpy(store[i].serv,temp.serv);
	}
	fin>>temp.wait;
	if((strcmp(temp.wait,store[i].wait))!=0)
	{
	strcpy(store[i].wait,temp.wait);
	}
	fin>>temp.file;
	if((strcmp(temp.file,store[i].file))!=0)
	{
	strcpy(store[i].file,temp.file);
	}
	if(flag==1)
	{
	close(sfd[i]);
	check[i]=1;
	}
	i++;   
	}
	else
	{
	fin>>store[i].no;
	fin>>store[i].proto;
	fin>>store[i].port;
	fin>>store[i].inext;
	fin>>store[i].limit;
	fin>>store[i].serv;
	fin>>store[i].wait;
	fin>>store[i].file;
	if(store[i-1].no!=store[i].no)
	{
	  check[i]=1;
	}
	i++;  
	}
  }
  i--;
  count=i;
  int rc;
  for(i=0;i<count;i++)
  {
  if(check[i]==1)
  {
  if((strcmp(store[i].proto,"TCP"))==0)
  {
     sfd[i]=socket(AF_INET,SOCK_STREAM,0);
     if(sfd[i]==-1){printf("could not create socket\n");exit(0);} 
     server.sin_family=AF_INET;
     server.sin_addr.s_addr=INADDR_ANY;
     server.sin_port=htons(store[i].port);
     rc=bind(sfd[i],(struct sockaddr *)&server,sizeof(server));
     if(rc<0){printf("tcp bind failed\n");exit(0);} 	
     listen(sfd[i],5);    	
  }
  else
  {
     sfd[i]=socket(AF_INET,SOCK_DGRAM,0);
     if(sfd[i]==-1){printf("could not create socket\n");exit(0);} 
     server.sin_family=AF_INET;
     server.sin_addr.s_addr=INADDR_ANY;
     server.sin_port=htons(store[i].port);
     rc=bind(sfd[i],(struct sockaddr *)&server,sizeof(server));
     if(rc<0){printf("udp bind failed\n");exit(0);} 	
  
  }
  }
  }
  printf("modifications completed\n");
}

void modify1(int arg)
{
  flag2=1;
  signal(SIGUSR2,modify1); 
}
void fun(int arg)
{
  
  store[sno[0]].count--;
  printf("store[%d]=%d\n",sno[0],store[sno[0]].count);
  signal(SIGUSR1,fun);
}

void *fun2(void *arg)
{
int i=*(int *)arg;
printf("in thread pno is %d\n",i);
len=sizeof(server);
int nsfd=accept(sfd[i],(struct sockaddr *)&client,&len);
int num=0,n;
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
if(store[i].limit!=0)
{
store[i].count--;
printf("store[%d]=%d\n",i,store[i].count);
}
}

void fun3(int arg)
{
  int rc;
  socklen_t frmlen;
  struct sockaddr_in server,from;
  frmlen = sizeof(struct sockaddr_in);
  sem_wait(&sem3);
       char buf[2000];
       memset(&buf,'\0',sizeof(buf));
       rc = recvfrom(sfd[arg],buf,2000,0,(struct sockaddr *)&from,&frmlen);
       if (rc < 0)
       {
       printf("recv error\n");
       exit(0);
       }
       rc = sendto(sfd[arg],buf,strlen(buf),0,(struct sockaddr *)&from,frmlen);
       if (rc < 0)
       {
       printf("send error\n");
       exit(0);
       }
  sem_post(&sem3);     
}




int main()
{
signal(SIGUSR1,fun);
signal(SIGUSR2,modify1);
ifstream fin;
fin.open("inetd_config.txt");
int i=0,rc,j,pid;
len=sizeof(server);
sem_init(&sem3,0,1);

key_t key=ftok(".",'a');
if((shmid=shmget(key,sizeof(int),IPC_CREAT|0666))==-1)
{
perror("shmget error\n");
exit(0);
}
sno=(int *)shmat(shmid,NULL,0);
sno[0]=0;

int shmid1;
int *id;
key_t key1=ftok(".",'d');
if((shmid1=shmget(key1,sizeof(int),IPC_CREAT|0666))==-1)
{
perror("shmget error\n");
exit(0);
}
id=(int *)shmat(shmid1,NULL,0);
id[0]=getpid();



while(!fin.eof())
{
fin>>store[i].no;
fin>>store[i].proto;
fin>>store[i].port;
fin>>store[i].inext;
fin>>store[i].limit;
fin>>store[i].serv;
fin>>store[i].wait;
fin>>store[i].file;
store[i].count=0;
i++;
}
fin.close();
i--;
count=i;
for(i=0;i<count;i++)
{
  if((strcmp(store[i].proto,"TCP"))==0)
  {
     sfd[i]=socket(AF_INET,SOCK_STREAM,0);
     if(sfd[i]==-1){printf("could not create socket\n");exit(0);} 
     server.sin_family=AF_INET;
     server.sin_addr.s_addr=INADDR_ANY;
     server.sin_port=htons(store[i].port);
     rc=bind(sfd[i],(struct sockaddr *)&server,sizeof(server));
     if(rc<0){printf("bind failed\n");exit(0);} 	
     listen(sfd[i],5);    	
  }
  else
  {
     sfd[i]=socket(AF_INET,SOCK_DGRAM,0);
     if(sfd[i]==-1){printf("could not create socket\n");exit(0);} 
     server.sin_family=AF_INET;
     server.sin_addr.s_addr=INADDR_ANY;
     server.sin_port=htons(store[i].port);
     rc=bind(sfd[i],(struct sockaddr *)&server,sizeof(server));
     if(rc<0){printf("bind failed\n");exit(0);} 	
  
  }
}

tv.tv_usec=0;tv.tv_sec=0;
printf("SERVER STARTED  %d\n",getpid());

while(1)
{
if(flag2==1)
{
modify();
flag2=0;
}
for(i=0;i<count;i++)
{
FD_SET(sfd[i],&rfds);
smax=max(smax,sfd[i]);
}
rc=select(smax+1,&rfds,NULL,NULL,(struct timeval *)&tv);
if(rc>0)
{

for(i=0;i<count;i++)
{ 
  if(FD_ISSET(sfd[i],&rfds))
  {
      printf("came in s%d\n",i);
      int flag;
      if((strcmp(store[i].serv,"process")==0))
      flag=0;
      else if((strcmp(store[i].serv,"thread")==0))
      flag=1;
      else if((strcmp(store[i].serv,"function")==0))
      flag=2;
      
      switch(flag)
      {
        case 0:  
        printf("its a process\n");          
        if(store[i].limit==0)
        {
          printf("no limit\n");
          int nsfd=accept(sfd[i],(struct sockaddr *)&client,&len);
          printf("accepted in s%d\n",i);
          int pid=fork();
          if(pid==0)
          {
          for(j=0;j<count;j++)
          close(sfd[j]);
          dup2(nsfd,0);
          printf("going to exec\n");
          execv(store[i].file,0);
          }
          else if(pid>0)
          {
          close(nsfd);
          }
        }
        else if(store[i].limit)
        {
        
        if(store[i].count>=store[i].limit)
        {
         printf("s%d in waiting state\n",i);
         
        }
        else
        {
          store[i].count++;
          printf("going to create a new process\n");
          int nsfd=accept(sfd[i],(struct sockaddr *)&client,&len);
          pid=fork();
          if(pid==0)
          {
          for(j=0;j<count;j++)
          close(sfd[j]);
          dup2(nsfd,0);
          char param[2],param1[2];
          int ppid=getppid();
          sprintf(param,"%d",ppid);
          sprintf(param1,"%d",i);
          printf("going to execl\n");
          execl(store[i].file,store[i].file,param,param1,(char *)0);
          }

        }
        
        }
        break;
        case 1:
        printf("its a thread\n");                  
        if(store[i].limit==0)
        {
        printf("no limit\n");
        pthread_t thr;
        int val;
        val=i;
        pthread_create(&thr,NULL,&fun2,(void *)&val);
        printf("thread_created\n");
        }
        else
        {
           if(store[i].count>=store[i].limit)
           {
            printf("s%d is in waiting state\n",i);
           }
           else
           {
             store[i].count++;
             pthread_t thr;
             int val;
             val=i;
             pthread_create(&thr,NULL,&fun2,(void *)&val);
           }
        }
        
        break;
        case 2:
        printf("its a function\n");                  
        fun3(i);
        printf("fuction called\n");
        break;
        
        default:printf("nothing matched\n");
        
      }
  }
}


}

}
}
