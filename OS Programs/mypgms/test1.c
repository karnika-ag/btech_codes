 
#include <stdio.h>
#include <sys/types.h>
#include <sys/sem.h>
#include <stdlib.h>
#include <sys/shm.h>
#include <errno.h>
#include<error.h>
#include <sys/ipc.h>
#include<pthread.h>
#define size 5
int mutex[5];
int *active;
int shmid;

void sem_acq(int semid)
{	
	struct sembuf sb;
	sb.sem_num=0;
	sb.sem_op=-1;
	sb.sem_flg=0;
	if((semop(semid,&sb,1))==-1)    
	{
		perror("\nFailed to acquire semaphore.");
		exit(0);
	}
}

void sem_rel(int semid)
{
	struct sembuf sb;
	sb.sem_num=0;
	sb.sem_op=1;
	sb.sem_flg=0;
	if((semop(semid,&sb,1))==-1)    
	{
		perror("\nFailed to release semaphore.");
		exit(0);
	}
}
void *work(void *val)
{

int p;
p=*(int *)val;

while(1)
{

sem_acq(mutex[p]);
sem_acq(mutex[(p+1)%5]);

active[p]=1;
printf("p %d [%d %d %d %d %d]\n",p+1,active[0],active[1],active[2],active[3],active[4]);   
sleep(1);
active[p]=0;

sem_rel(mutex[p]);
sem_rel(mutex[(p+1)%5]);

sleep(2);
}
exit(0);
}

int main()
{

int i,pid;

for(i=0;i<5;i++)
{

if((mutex[i]=semget(IPC_PRIVATE,1,0666|IPC_CREAT))==-1)
{
   perror("error in create semaphore\n");
   exit(0);
}

if((semctl(mutex[i],0,SETVAL,1))==-1)
{
int errsn=errno;
printf(" %d %d ",mutex[i],errno);
perror("error in semctl semaphore\n");
if(errsn==EEXIST)
printf("already exist\n");
exit(0);
}

}

if((shmid=shmget(IPC_PRIVATE,size*sizeof(int),0666|IPC_CREAT))==-1)
{
   perror("shmget error\n");
   exit(0);
}

active=(int *)shmat(shmid,NULL,0);

for(i=0;i<5;i++)
active[i]=0;


int arr[5];
i=0;
for(i=0;i<4;i++)
{
pid=fork();

if(pid==0)
{
work((void *)&i);
exit(0);
}
 

}
work((void *)&i);
exit(0);
return 0;
}
 