#include<stdio.h>
#include<pthread.h>
#include<semaphore.h>
sem_t mutex,writeblock;
int data=0,rcount=0;


void reader(void *val)
{
int arg=*(int *)val;
while(1)
{
  printf("reader %d came\n",arg);
  sem_wait(&mutex);
  rcount++;
  if(rcount==1)
  sem_wait(&writeblock);
  sem_post(&mutex);
  printf("reader %d reading data\n",arg);
  sleep(2); 
  printf("reader %d finished reading data\n",arg);
  sem_wait(&mutex);
  rcount--;
  if(rcount==0)
  sem_post(&writeblock);
  sem_post(&mutex);
  sleep(1);
}
exit(0);
}


void writer(void *val)
{
int arg=*(int *)val;
printf("writer %d came\n",arg);
while(1)
{
   sem_wait(&writeblock);
   printf("writer %d writing data\n ",arg);
    sleep(2);  
// sleep(rand()%3 + 3);
   printf("writer %d finished writing data\n ",arg);
   sem_post(&writeblock);
   sleep(5);
}
}



int main()
{
pthread_t r[5],w[5];
int i;
sem_init(&mutex,0,1);
sem_init(&writeblock,0,1);
int arr[5];
for(i=0;i<5;i++)
{
arr[i]=i;
pthread_create(&r[i],NULL,(void *)&reader,(void *)&arr[i]);
pthread_create(&w[i],NULL,(void *)&writer,(void *)&arr[i]);
}


for(i=0;i<5;i++)
{
pthread_join(r[i],NULL);
pthread_join(w[i],NULL);
}

return 0;
}
