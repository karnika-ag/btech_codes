#include<stdio.h>
#include<pthread.h>
pthread_mutex_t mutex1,mutex2,W,R;
int rcount=0,wcount=0,data=0;
void reader(void *arg)
{
	int t=*(int *)arg;
        printf("reader %d reading\n",t);
	while(1)
	{
	 pthread_mutex_lock(&R);
	  pthread_mutex_lock(&mutex1);
	  rcount++;
	  if(rcount==1)	
	  pthread_mutex_lock(&W);
	  pthread_mutex_unlock(&mutex1);
	 pthread_mutex_unlock(&R);  
	 
	 printf("reader %d reading data %d \n",t,data);
	 sleep(1);
	  pthread_mutex_lock(&mutex1);
	  rcount--;
	  if(rcount==0)	
	  pthread_mutex_unlock(&W);
	  pthread_mutex_unlock(&mutex1);
	 
	  
	}
	exit(0);
}

void writer(int *arg)
{
  int t=*(int *)arg;
  printf("writer %d writing\n",t);
  while(1)	
  {
  	pthread_mutex_lock(&mutex2);
  	wcount++;
  	if(wcount==1)
  	pthread_mutex_lock(&R);
  	pthread_mutex_unlock(&mutex2);
  	
  	pthread_mutex_lock(&W);
  	data++;
  	printf("writer %d writing data %d \n",t,data);
  	sleep(2);
  	pthread_mutex_unlock(&W);
  	
  	pthread_mutex_lock(&mutex2);
  	wcount--;
  	if(wcount==0)
  	pthread_mutex_unlock(&R);
  	pthread_mutex_unlock(&mutex2);
         
       sleep(8); 	
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
