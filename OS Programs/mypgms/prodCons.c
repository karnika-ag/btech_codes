#include <stdio.h>
#include <sys/types.h>
#include <sys/sem.h>
#include <stdlib.h>
#include <sys/shm.h>
#include <errno.h>
#include <sys/ipc.h>
void sem_acq(int);
void sem_rel(int);
int count=1;
int *buffer;
int in=-1,out=-1;
int n;
int mutex,empty,full,shmid;
pid_t ret;
int producer()
{
	while(1)
	{
		sem_acq(mutex);
		if((in+1)%n==out)
		{
			sem_acq(empty);
		}
		printf("Item produced: %d\n",count);
		in = (in+1)%n;
		buffer[in]=count;
		count++;
		sem_rel(mutex);
		if((out+1)%5==in)
		sem_rel(full);
		sleep(rand()%5); 
	}
	exit(1);
}
int consumer()
{
	while(1)
	{
		sem_acq(mutex);
		if(in==out)
		{
			sem_acq(full);
		}
		out = (out+1)%n;
		printf("\nItem consumed: %d\n",buffer[out]);
		sem_rel(mutex);
		if((in+2)%n==out)
		sem_rel(empty);
		sleep(rand()%3);
	}
	exit(1);
}
int main()
{       
	int k;   
	char c[2];
	printf("\nProducer Consumer Problem using Semaphore\n");
	printf("\nEnter the size for buffer:");
	//scanf(“%d”, &n);
	n=10;


	/*---------------------------creation of sem------------------------------------------------*/
	if((mutex=semget(IPC_PRIVATE,1,0666|IPC_CREAT))==-1) 
	{
		perror("\nFailed to create semaphore.");
		exit(0);
	}
	if((semctl(mutex,0,SETVAL,1))==-1) 
	{
		perror("\nFailed to set value for the semaphore.");
		exit(0);
	}
	if((empty=semget(IPC_PRIVATE,1,0666|IPC_CREAT))==-1) 
	{
		perror("\nFailed to create semaphore.");
		exit(0);
	}
	if((semctl(empty,0,SETVAL,n))==-1) 
	{
		perror("\nFailed to set value for semaphore.");
		exit(0);
	}
	if((full=semget(IPC_PRIVATE,1,0666|IPC_CREAT))==-1) 
	{
		perror("\nFailed to create semaphore.");
		exit(0);
	}

	if((semctl(full,0,SETVAL,0))==-1) 
	{
		perror("\nFailed to set value for the semaphore.");
		exit(0);
	}
	if((shmid=shmget(IPC_PRIVATE,n*sizeof(int),0666|IPC_CREAT))==-1) 
	{
		perror("\nFailed to allocate shared memory.");
		exit(0);
	}

	/*-----------------------------------------------------------*/



	
	buffer=(int *)shmat(shmid,(const void *)0,0);
	ret=fork();
	if(ret==0)
	producer();
	else
	k=consumer();
	exit(1);

	//ret=fork();
	//exit(consumer());
}
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
