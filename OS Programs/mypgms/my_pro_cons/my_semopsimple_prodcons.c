#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/ipc.h>
#include<sys/sem.h>
#include<sys/types.h>
#define size 5

int mutex,full,empty;//mutex=0,full=1,empty=2
int start=0,end=0,data=0;
int *buffer;
int shmid;

void semlock(int semid)
{

struct sembuf tmp;
tmp.sem_num=0;
tmp.sem_op=-1;
tmp.sem_flg=0;
if((semop(semid,&tmp,1))==-1)
{
perror("semop lock error\n");
exit(0);
}

}


void semunlock(int semid)
{
struct sembuf tmp;
tmp.sem_num=0;
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
     semlock(empty);
       semlock(mutex);
         data++;
         printf("producer produced %d \n",data);
         end=(end+1)%size;
         buffer[end]=data;
       semunlock(mutex);
     semunlock(full);
         sleep(rand()%8);        
  }

}

void consumer()
{
  while(1)
  {
     semlock(full);
       semlock(mutex);
         start=(start+1)%size;
        printf(" consumer consumed %d \n",buffer[start]);
          semunlock(mutex);
      semunlock(empty);
        sleep(rand()%12);        
  }
}


int main()
{
int i,rc,pid;


if((mutex=semget(IPC_PRIVATE,1,IPC_CREAT|0666))==-1)
{
perror("semget error\n");
exit(0);
}

if((semctl(mutex,0,SETVAL,1))==-1)
{
perror("semctl error\n");
exit(0);
}


if((full=semget(IPC_PRIVATE,1,IPC_CREAT|0666))==-1)
{
perror("semget error\n");
exit(0);
}

if((semctl(full,0,SETVAL,0))==-1)
{
perror("semctl error\n");
exit(0);
}


if((empty=semget(IPC_PRIVATE,1,IPC_CREAT|0666))==-1)
{
perror("semget error\n");
exit(0);
}

if((semctl(empty,0,SETVAL,size))==-1)
{
perror("semctl error\n");
exit(0);
}


if((shmid=shmget(IPC_PRIVATE,size*sizeof(int),0666|IPC_CREAT))==-1)
{
perror("shnget error\n");
exit(0);
}

buffer=(int *)shmat(shmid,NULL,0);
pid=fork();
if(pid==0)
{
producer();
}
else if(pid>0)
consumer();
else
return 0;


/*
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
*/
return 0;

}
