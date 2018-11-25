#include<sys/select.h>
#include<sys/stat.h>
#include<stdio.h>
#include<sys/types.h>
#include <unistd.h>
#include <fcntl.h>
#include<stdlib.h>
#include<signal.h>
#include<sys/ipc.h>
#include<sys/shm.h>
#include <sys/poll.h>
#include <sys/time.h>

#define MAX 9

int shmid;
int *no;
int prc=0;
int csfd[MAX];
int scfd[MAX];
char myfifo1[12]="ctos_fifo1";
char myfifo2[12]="stoc_fifo1";
int n=0;
fd_set rfds;
struct timeval tv;

int max(int a,int b)
{
if(a>b)return a;
return b;
}

void fun2()
{
while(1)
{
if(no[0]>prc)
{
//   prc=no[0];
   myfifo1[9]=(char)no[0]+'0';
   myfifo1[10]='\0';
   myfifo2[9]=(char)no[0]+'0';
   myfifo2[10]='\0';   
   csfd[no[0]]= open(myfifo1, O_RDWR);
   scfd[no[0]]= open(myfifo2, O_RDWR);
   printf("pipe%d created\n",no[0]);
   FD_SET(csfd[no[0]],&rfds);
   n=max(n,csfd[no[0]]);
   prc=no[0];
   //signal(SIGUSR1,fun2);
}
}
exit(0);
}

void fun1()
{

char str[500];
int i,j,k;
int retval;

while(1)
{

for(i=1;i<=prc;i++)
{
FD_SET(csfd[i],&rfds);
n=max(n,csfd[i]);
}
retval = select (n + 1, &rfds, NULL, NULL, NULL);
if (retval < 0) 
   {
            perror ("select()");
            exit (1);
   }
for(i=1;i<=prc;i++)
{
  if(FD_ISSET(csfd[i],&rfds))
  {
      int n = read(csfd[i],str,sizeof(str));
      str[n]='\0';
      printf("SERVER: %d bytes message from CLIENT %d : %s \n",n,i,str);
      
				for(j=1;j<=prc;j++)
				{
					if(j!=i)
					{
						write(scfd[j],str,sizeof(str));
					}    
				}   
  }
}
}
}

int main()
{
//signal(SIGUSR1,fun2);
int i;
if((shmid=shmget(2274,5*sizeof(int),IPC_CREAT|0666))==-1)
{
perror("shmget error\n");
exit(0);
}
no=(int *)shmat(shmid,NULL,0);
no[0]=0;
no[1]=getpid();
   printf("%d \n",no[1]);

for(i=1;i<=prc;i++)
   {  
   myfifo1[9]=(char)i+'0';
   myfifo1[10]='\0';
   myfifo2[9]=(char)i+'0';
   myfifo2[10]='\0';   
   mkfifo(myfifo1,0666);
   mkfifo(myfifo2,0666);
   csfd[i]= open(myfifo1, O_RDWR);
   scfd[i]= open(myfifo2, O_RDWR);
   printf("pipe%d created\n",i);
   }
   
   printf("SERVER STARTED\n");
   
   pthread_t thr[2];
   int rc;
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
 
   for(i=1;i<=prc;i++)
   {
    close(csfd[i]);
    close(scfd[i]);
    myfifo1[9]=i+'0';
    myfifo1[10]='\0';    
    myfifo2[9]=i+'0';
    myfifo2[10]='\0';
    unlink(myfifo1);
    unlink(myfifo2);
   }
   
 return 0;
 }
