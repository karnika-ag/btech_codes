#include<stdio.h>
#include<pthread.h>
pthread_mutex_t R,W,mutex;
int rc=0,data=0;
void reader(void *arg)
{
	int t=*(int *)arg;
	while(1)
	{
	  pthread_mutex_lock(&R);
	  pthread_mutex_lock(&mutex);	
	  rc++;
	  if(rc==1)
	  pthread_mutex_lock(&W);
	  pthread_mutex_unlock(&mutex);
	  pthread_mutex_unlock(&R);
	  
	  printf("reader %d reading data %d\n",t,data);
	  sleep(1);
	  
	  pthread_mutex_lock(&mutex);	
	  rc--;
	  if(rc==0)
	  pthread_mutex_unlock(&W);
	  pthread_mutex_unlock(&mutex);
	  
	}
	exit(0);
}

void writer(void *arg)
{
	int t=*(int *)arg;
	while(1)
	{
	  pthread_mutex_lock(&R);
	  pthread_mutex_lock(&W);
	  pthread_mutex_unlock(&R);
	  data++;
	  printf("writer %d writing %d \n",t,data);
	  sleep(1);
	  pthread_mutex_unlock(&W);
	}
	exit(0);
}

int main()
{
	pthread_t r[5],w[5];
	int id[5],i;
	for(i=0;i<5;i++)
	{
		id[i]=i+1;
		pthread_create(&r[i],NULL,(void *)&reader,(void *)&id[i]);
		pthread_create(&w[i],NULL,(void *)&writer,(void *)&id[i]);
	}
	for(i=0;i<5;i++)
	{
		pthread_join(r[i],NULL);
		pthread_join(w[i],NULL);
	}
	return 0;
}
