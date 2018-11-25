#include<sys/ipc.h>
#include<stdio.h>
#include<sys/shm.h>
#include<sys/sem.h>
#include<stdlib.h>
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
 char *myfifo1 = "ctos_fifo2";
 int scfd;
 char *myfifo2 = "stoc_fifo2";


void fun1()
{

   char str[BUFSIZ];
   printf("CLIENT 2: enter msg \n");
   scanf("%s", str);
   write(csfd, str, sizeof(str));
   cid[2]=1;
   kill(sid,SIGUSR1);
   perror("write:\n");
 
}

void fun2()
{
   signal(SIGUSR1,fun2);
   char str[BUFSIZ];
   read(scfd,str,sizeof(str));
   perror("Read:\n"); 
   printf("CLIENT 2: received from server:- %s\n",str);
  
  
}

int main()
{
signal(SIGUSR1,fun2);
int i,rc;
//key_t key=ftok('.',123);

if((shmid=shmget(2277,5*sizeof(int),IPC_CREAT|0666))==-1)
{
perror("shmget error\n");
exit(0);
}
cpid=(int *)shmat(shmid,NULL,0);
cpid[2]=getpid();
printf("client2 id- %d\n",cpid[2]);

if((shmid1=shmget(3277,5*sizeof(int),IPC_CREAT|0666))==-1)
{
perror("shmget error\n");
exit(0);
}

cid=(int *)shmat(shmid1,NULL,0);
cid[2]=0;



   csfd = open(myfifo1, O_RDWR);
   scfd = open(myfifo2, O_RDWR);

  printf("CLIENT2 READY\n"); 
 read(scfd,&sid,sizeof(sid));   
 perror("read:");
 printf("server pid %d\n",sid);
 while(1)
   fun1();
 
   close(csfd);
   close(scfd);


   return 0;
}
