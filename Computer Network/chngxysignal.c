#include<signal.h>
#include<stdio.h>
#include<sys/shm.h>
#include<sys/sem.h>
#include<stdlib.h>
int shmid;
int shmpid;
int semid;
int *x;
int *y;
int *buffer;
int *pid;
int p2;
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
     *x=*y+1;
     printf("fun1 %d\n",*x);
     signal(SIGUSR1,fun1); 
;
     kill(p2,SIGUSR2);
     sleep(2);
}


int main()
{
signal(SIGUSR1,fun1);
int i,rc;
key_t key=1234;
if((semid=semget(key,1,IPC_CREAT|0666))==-1)
{
perror("semget error\n");
exit(0);
}
if((semctl(semid,0,SETVAL,0))==-1)
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


if((shmid=shmget(1235,sizeof(int),IPC_CREAT|0666))==-1)
{
perror("shmget error\n");
exit(0);
}
pid=(int *)shmat(shmid,NULL,0);


*pid=getpid();
semunlock(0);
sleep(2);
semlock(0);
p2=*pid;

printf("%d\n%d\n",getpid(),p2);

fun1();

while(1);

  return 0;
}



