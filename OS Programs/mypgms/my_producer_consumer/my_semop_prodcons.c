#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/ipc.h>
#include<sys/sem.h>
#include<sys/types.h>
#define size 5

union semun
{
int val;
struct semid_ds *buf;
unsigned short *array;
};


//int mutex,full,empty;//mutex=0,full=1,empty=2
int semid,start=0,end=0,data=0;
int buffer[size];

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
        printf(" consumer consumed %d \n",buffer[start]);
          semunlock(semid,0);
      semunlock(semid,2);
        sleep(rand()%12);        
  }
}


int main()
{
int i,rc;
key_t key=1234;
union semun buf;
if((semid=semget(key,3,IPC_CREAT|0666))==-1)
{
perror("semget error\n");
exit(0);
}

ushort values[]={1,0,size};
buf.array=values;

if((semctl(semid,3,SETALL,buf))==-1)
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
