#include<stdlib.h>
#include<stdio.h>
#include<pthread.h>
#include<semaphore.h>
#define size 5
sem_t mutex,full,empty;
int data=0;
int start=0,end=0;
int buffer[size];

void producer()
{
 
  while(1)
  {
     sem_wait(&empty);
       sem_wait(&mutex);
        data++;
        printf("producer produced %d \n",data);
         end=(end+1)%size;
         buffer[end]=data;
        sem_post(&mutex);
      sem_post(&full);
        sleep(rand()%8);        
  }
}


void consumer()
{
  printf("consumer came\n");
  while(1)
  {
     sem_wait(&full);
       sem_wait(&mutex);
         start=(start+1)%size;
        printf(" consumer consumed %d \n",buffer[start]);
          sem_post(&mutex);
      sem_post(&empty);
        sleep(rand()%12);        
  }
}


int main()
{

int rc,i;

sem_init(&mutex,0,1);
sem_init(&full,0,0);
sem_init(&empty,0,size);

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

sem_destroy(&mutex);
sem_destroy(&full);
sem_destroy(&empty);

return 0;
}
