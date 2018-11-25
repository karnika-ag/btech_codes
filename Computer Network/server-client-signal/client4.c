#include<stdio.h>
#include<sys/shm.h>
#include<sys/sem.h>
#include<stdlib.h>
#include<sys/ipc.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include<stdlib.h>
#include<signal.h>
#include <unistd.h>
int shmid,shmid1;
int *cpid,*cid;
int sid,pid; 
 int csfd;
 char *myfifo1 = "ctos_fifo4";
 int scfd;
 char *myfifo2 = "stoc_fifo4";


void fun1()
{

   char str[BUFSIZ];
   printf("CLIENT 4: enter msg \n");
   scanf("%s", str);
   write(csfd, str, sizeof(str));
   cid[4]=1;
   kill(sid,SIGUSR1);
   perror("write:\n");
    
}

void fun2()
{
   signal(SIGUSR1,fun2);
   char str[BUFSIZ];
   read(scfd,str,sizeof(str));
   perror("Read:\n"); 
   printf("CLIENT 4: received from server:- %s\n",str);
  
}

int main()
{
signal(SIGUSR1,fun2);
int i,rc;
if((shmid=shmget(2277,5*sizeof(int),IPC_CREAT|0666))==-1)
{
perror("shmget error\n");
exit(0);
}

cpid=(int *)shmat(shmid,NULL,0);
cpid[4]=getpid();
printf("client4 id- %d\n",cpid[4]);

if((shmid1=shmget(3277,5*sizeof(int),IPC_CREAT|0666))==-1)
{
perror("shmget error\n");
exit(0);
}

cid=(int *)shmat(shmid1,NULL,0);
cid[4]=0;


   csfd = open(myfifo1, O_RDWR);
   scfd = open(myfifo2, O_RDWR);
 
  printf("CLIENT4 READY\n");
 read(scfd,&sid,sizeof(sid));   
 perror("read:");
 printf("server pid %d\n",sid);
 while(1)
   fun1();
 
   close(csfd);
   close(scfd);


   return 0;
}
