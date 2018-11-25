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
int semid;
int shmid;
int *buffer;
int server;
   int csfd;
   char *myfifo1 = "ctos_fifo4";
   int scfd;
   char *myfifo2 = "stoc_fifo4";


union semun
{
int val;
struct semid_ds *buf;
unsigned short *array;
};

void semlock(int index)
{
struct sembuf temp;
temp.sem_num=index;
temp.sem_op=-1;
temp.sem_flg=0;
if((semop(semid,&temp,1))==-1)
{
perror("semop error\n");
exit(0);
}
}
void semunlock(int index)
{
struct sembuf temp;
temp.sem_num=index;
temp.sem_op=1;
temp.sem_flg=0;
if((semop(semid,&temp,1))==-1)
{
perror("semop error\n");
exit(0);
}
}

void fun1()
{

   char str[BUFSIZ];
   while(1)
   {
   printf("CLIENT 4: enter msg \n");
   scanf("%s", str);
   write(csfd, str, sizeof(str));
   kill(server,SIGUSR1);
   perror("write:\n");
   sleep(2);
   }
   exit(0);
 
}

void fun2()
{
   signal(SIGUSR1,fun2);
   char str[BUFSIZ];
   
   read(scfd,str,sizeof(str));
   perror("Read:\n"); 
   printf("CLIENT 4: received from server:- %s\n",str);
   sleep(2);
  
}
int main()
{

signal(SIGUSR1,fun2);
int i,rc;
key_t key=4567;
if((semid=semget(key,5,IPC_CREAT|0666))==-1)
{
perror("semget error\n");
exit(0);
}
union semun buf;
ushort values[]={0,0,0,0,0};
buf.array=values;
if((semctl(semid,5,SETALL,buf))==-1)
{
perror("semctl error \n");
exit(0);
}

if((shmid=shmget(4567,5*sizeof(int),IPC_CREAT|0666))==-1)
{
perror("shmget error\n");
exit(0);
}

buffer=(int *)shmat(shmid,NULL,0);
buffer[4]=getpid();
semunlock(4);

   csfd = open(myfifo1, O_WRONLY);
   scfd = open(myfifo2, O_RDONLY);
   
   semlock(0);
   server=buffer[0];
   semunlock(0);
  
    fun1();
 
   close(csfd);
   close(scfd);


   return 0;
}
