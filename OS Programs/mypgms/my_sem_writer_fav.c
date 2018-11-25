#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/sem.h>
#include<sys/ipc.h>
#include<sys/shm.h>
#include<errno.h>
//int mutex,writelock,access,read; mutex=0,writelock=1,access=2,read=3
int shmid,semid;
int *id,rcount=0,wcount=0;
union semun
{
int val;
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
perror("semop lock error\n");
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
perror("semop unlock error\n");
exit(0);
}
}

void reader(void *val)
{
int arg=*(int *)val;
printf("reader %d has come\n",arg);
while(1)
{
  semlock(semid,0);
  if(wcount>0)
   semlock(semid,3);
  rcount++;
  if(wcount==0)
  semlock(semid,1);
  semunlock(semid,0);
  printf("reader %d reading data\n",arg);
  sleep(2); 
  printf("reader %d finished reading data\n",arg);
  semlock(semid,0);
  rcount--;
  if(rcount==0)
  semunlock(semid,1);
  semunlock(semid,0);
  sleep(1);
}
exit(0);
}

void writer(void *val)
{
int arg=*(int *)val;
 printf("writer %d has come\n",arg);
while(1)
{
   semlock(semid,0);
   wcount++;
   if(wcount==1)
   {
      semlock(semid,3);
      semlock(semid,1);
   }
   semunlock(semid,0);
   semlock(semid,2);
   printf("writer %d writing data\n ",arg);
   sleep(2);  
   printf("writer %d finished writing data\n ",arg);
   semunlock(semid,2);
   semlock(semid,0);
   wcount--;
   if(wcount==0)
   {
     semunlock(semid,3);
     semunlock(semid,1);
   }
   semunlock(semid,0);
   sleep(5);
}
exit(0);
}

int main()
{

int i,rc,pid;
key_t key=9876;
union semun buf;
if((semid=semget(key,4,IPC_CREAT|0666))==-1)
{
perror("semget error\n");
exit(0);
}

ushort values[]={1,1,1,1};
buf.array=values;

if((semctl(semid,4,SETALL,buf))==-1)
{
perror("semctl error\n");
exit(0);
}

/*
if((shmid=shmget(IPC_PRIVATE,sizeof(int),0666|IPC_CREAT))==-1)
{
perror("shmget error\n");
exit(0);
}

id=(int *)shmat(shmid,NULL,0);

for(i=0;i<5;i++)
{
  pid=fork();
  if(pid==0)
   writer(i);
  pid=fork();
  if(pid==0)
   reader(i);

}
*/

pthread_t r[2],w[2];
int arr[2];
for(i=0;i<2;i++)
{
arr[i]=i;
pthread_create(&r[i],NULL,(void *)&reader,(void *)&arr[i]);
pthread_create(&w[i],NULL,(void *)&writer,(void *)&arr[i]);

}


for(i=0;i<5;i++)
{
pthread_join(r[i],NULL);
pthread_join(w[i],NULL);
}

wait(2);
return 0;

}


