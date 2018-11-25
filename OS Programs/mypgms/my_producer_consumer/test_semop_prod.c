#include<stdio.h>
#include<sys/types.h>
#include<sys/ipc.h>
#include<sys/sem.h>
#include<stdlib.h>
#define size 5
int sem_id,start=0,end=0,data=0;
int buffer[size];
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
perror("error in semop\n");
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
perror("error in semop unlock\n");
exit(0);
}
}


void producer()
{
while(1)
{
  semlock(sem_id,2);
  semlock(sem_id,0);
   data++;
   printf("producer produced data %d\n",data);
   end=(end+1)%size;
   buffer[end]=data;
  semunlock(sem_id,0);
  semunlock(sem_id,1);
  sleep(rand()%8);
}
exit(0);
}



void consumer()
{
while(1)
{
  semlock(sem_id,1);
  semlock(sem_id,0);
   start=(start+1)%size;
   printf("consumer consumed data %d\n",buffer[start]);
  semunlock(sem_id,0);
  semunlock(sem_id,2);
  sleep(rand()%12);
}
exit(0);
}


int main()
{
int i,rc;
if((sem_id=semget(IPC_PRIVATE,3,IPC_CREAT|0666))==-1)
{
perror("semget error\n");
exit(0);
}  

union semun buf;
ushort values[]={1,0,size};
buf.array=values;


if((semctl(sem_id,3,SETALL,buf))==-1)
{
perror("semctl error\n");
exit(0);
}

pthread_t p[2],c[2];

for(i=0;i<2;i++)
{

if(rc=(pthread_create(&p[i],NULL,(void *)&producer,NULL)))
{
perror("error in producer thread create\n");
exit(0);
}

if(rc=(pthread_create(&c[i],NULL,(void *)&consumer,NULL)))
{
perror("error in consumer thread create\n");
exit(0);
}

}

for(i=0;i<2;i++)
{
pthread_join(p[i],NULL);
pthread_join(c[i],NULL);
}



return 0;

}
