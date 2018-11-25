#include<stdio.h>
#include<sys/shm.h>
#include<sys/sem.h>
#include<stdlib.h>
int shmid;
int semid;
int *x;
int *y;
int *buffer;
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
  while(1)
  {
     semlock(1);
     *x=*y+1;
     printf("fun1 %d\n",*x);
     semunlock(0);
     sleep(5);     
  }
  exit(0);
}


int main()
{
int i,rc;
key_t key=1234;
if((semid=semget(key,2,IPC_CREAT|0666))==-1)
{
perror("semget error\n");
exit(0);
}
union semun buf;
ushort values[]={0,1};
buf.array=values;
if((semctl(semid,2,SETALL,buf))==-1)
{
perror("semctl error \n");
exit(0);
}

if((shmid=shmget(1234,2*sizeof(int),IPC_CREAT|0666))==-1)
{
perror("shmget error\n");
exit(0);
}

buffer=(int *)shmat(shmid,NULL,0);
x=buffer;
y=buffer+1;
*x=1;*y=2;


  fun1();

  return 0;
}



