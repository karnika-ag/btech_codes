#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/ipc.h>
#include<sys/shm.h>
#include<sys/sem.h>
#include<errno.h>
#define size 5
int *buffer;
int start=0,end=0,data=0;
int semid;
int shmid;
union semun
{
int data;
struct semid_ds *buf;
unsigned short *array;
};

void semlock(int semid,int semindex)
{
struct sembuf tmp;
tmp.sem_num=semindex;
tmp.sem_op=-1;
tmp.sem_flg=0;
if((semop(semid,&tmp,1))==-1)
{
perror("semop error in semlock\n");
exit(0);
}
}

void semunlock(int semid,int semindex)
{
struct sembuf tmp;
tmp.sem_num=semindex;
tmp.sem_op=1;
tmp.sem_flg=0;
if((semop(semid,&tmp,1))==-1)
{
perror("semop error in semunlock\n");
exit(0);
}
}

void producer()
{
 while(1)
 {
   semlock(semid,2);
    semlock(semid,0);
     data++;
     printf("producer produced %d \n",data);
     end=(end+1)%size;
     buffer[end]=data;
    semunlock(semid,0);
   semunlock(semid,1);
   sleep(rand()%8);     
 }
}



void consumer()
{
 while(1)
 {
   semlock(semid,1);
    semlock(semid,0);
     start=(start+1)%size;
     printf("consumer consumed %d \n",buffer[start]);
    semunlock(semid,0);
   semunlock(semid,2);
 sleep(rand()%12);     
 }
}


int main()
{
   int pid,i;
 union semun tmp;

      if((semid=semget(IPC_PRIVATE,3,IPC_CREAT|0666))==-1)
	{
	perror("semget error\n");
	exit(0);
	}

           ushort values[]={1,0,size};      
	   tmp.array=values;

	if((semctl(semid,3,SETALL,tmp))==-1)
	{
	perror("semget error\n");	
	exit(0);
	}

if((shmid=shmget(IPC_PRIVATE,size*sizeof(int),IPC_CREAT|0666))==-1)
{
perror("semget error\n");	
exit(0);
}

buffer=(int *)shmat(shmid,NULL,0);

pid=fork();

if(pid==0)
producer();
else if(pid>0)
consumer();
else
return 0;

return 0;
}


