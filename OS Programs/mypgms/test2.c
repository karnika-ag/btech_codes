#include<stdio.h>
#include<pthread.h>
#include<semaphore.h>
#include <stdlib.h>
sem_t mutex,writeblock,counter;
int data=0,rcount=0;
/*
void writer(void *val)
{
	int id=*(int *)val;
 printf("writer %d has come \n",id);
 while(1)
 {
 	
  //sem_wait(&mutex);
  sem_wait(&writeblock);
  printf("Writer %d is writing\n",id);
  sleep(2);
  printf("Writer %d is  done writing\n",id);
  //sem_post(&mutex);
  sem_post(&writeblock);
  sleep(5);
 }
 exit(id);
}
void reader(void *val)
{
	int id=*(int *)val;
 printf("Reader %d has come\n",id );
 while(1)
 {
  //sem_wait(&mutex);
  sem_wait(&counter);
  rcount++;

  if(rcount==1)
   sem_wait(&writeblock);
  sem_post(&counter);
  //sem_post(&mutex);
  printf("reader %d is reading\n",id);
sleep(2);
  printf("reader %d is done reading\n",id);
  sem_wait(&counter);
   rcount--;
  if(rcount==0)
   sem_post(&writeblock);
  sem_post(&counter);
  sleep(1);
 }
 exit(id);
}

*/
void reader(void *val)
{
int arg=*(int *)val;
printf("Reader %d has come\n",arg );
while(1)
{
	//sem_wait(&mutex);
  sem_wait(&counter);
  rcount++;
  if(rcount==1)
  sem_wait(&writeblock);
  sem_post(&counter);
  //sem_post(&mutex);
  printf("reader %d reading data \n",arg);
  sleep(2); 
 // sleep(rand()%5);
  printf("reader %d finished reading data\n",arg);
  sem_wait(&counter);
  rcount--;
  if(rcount==0)
  sem_post(&writeblock);
  sem_post(&counter);
  sleep(1);
 // sleep(rand()%3);
}
exit(0);
}

void writer(void *val)
{
int arg=*(int *)val;
printf("writer %d has come \n",arg);
while(1)
{
   sem_wait(&writeblock);
   //sem_wait(&mutex);
   printf("writer %d writing data\n ",arg);
    sleep(2);  
// sleep(rand()%3 + 3);
   printf("writer %d finished writing data\n ",arg);
   //sem_post(&mutex);
   sem_post(&writeblock);
   sleep(5);
}
exit(0);
}

int main()
{
pthread_t r[5],w[5];
int i;
sem_init(&mutex,0,1);
sem_init(&writeblock,0,1);
sem_init(&counter,0,1);
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
