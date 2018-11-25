 

#include <stdio.h>
#include <sys/types.h>
#include <sys/sem.h>
#include <stdlib.h>
#include <sys/shm.h>
#include <errno.h>
#include <semaphore.h>
#include <pthread.h>
int mutex[5];
//sem_t mt;
int active[5];

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
	int i=0;
	printf("%d prco ccomes\n",p);
	for(i=0;i<5;i++)
	{
		//sem_wait(&mt);
		//sem_wait(&mutex[p]);
		//sem_wait(&mutex[(p+1)%5]);
                 sem_acq(mutex[p]);
                 sem_acq(mutex[(p+1)%5]);
		active[p]=1;
		printf("pasd %d [%d %d %d %d %d]\n",p+1,active[0],active[1],active[2],active[3],active[4]);   
		sleep(2);
		active[p]=0;
		//printf("hi %d \n",p);
		//sem_post(&mutex[p]);
		//sem_post(&mutex[(p+1)%5]);
		//sem_post(&mt);
                 sem_rel(mutex[p]);
                sem_rel(mutex[(p+1)%5]);
		sleep(2);
		//printf("hi\n");
	}
	exit(p);
}

int main()
{
	int i;
	int ar[5],arr[5];
	for(i=0;i<5;i++)
	{
         
	 if(mutex[i]=semget(i+1000,1,0666|IPC_CREAT)==-1)
	 {
	  perror("error in create semaphore\n");
	   exit(0);
	 }
	  if((semctl(mutex[i],0,SETVAL,1))==-1)
	{
	perror("error in semctl semaphore\n");
	exit(0);
	//ar[i]=i;
	//sem_init(&mutex[i],0,1);
	}

	}
	//sem_init(&mt,0,0);

	for(i=0;i<5;i++)
	active[i]=0;

	pthread_t pid[5];

	//pthread_setconcurrency(6);
	for(i=0;i<5;i++)
	{
	      	arr[i]=i;
		pthread_create(&pid[i],NULL,work,(void *)&arr[i]);
	}

	//for(i=0;i<5;i++)
	pthread_join(pid[0],NULL);

}
 
