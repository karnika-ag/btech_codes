#include<stdio.h>
#include<pthread.h>
#define MAX 10
pthread_mutex_t mutex=PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t pro=PTHREAD_COND_INITIALIZER;
pthread_cond_t con=PTHREAD_COND_INITIALIZER;
int buffer[MAX],start=0,end=0,data=0;

void producer()
{
  while(1)
  {
     pthread_mutex_lock(&mutex);
     data++;
     if((end+1)%MAX==start)
     pthread_cond_wait(&pro,&mutex);
     end=(end+1)%MAX;
     buffer[end]=data;
     printf("producer produced %d\n ",data);
     if((start+1)%MAX==end)
     pthread_cond_signal(&con);
     pthread_mutex_unlock(&mutex);
      sleep(rand()%8);
     
  }
}

void consumer()
{
 while(1)
  {
    
    pthread_mutex_lock(&mutex);
    if(end==start)
    pthread_cond_wait(&con,&mutex);
    start=(start+1)%MAX;
    printf("consumer consumed %d\n",buffer[start]);
    if((end+2)%MAX==start)
    pthread_cond_signal(&pro);
    pthread_mutex_unlock(&mutex);
    sleep(rand()%12);
  }

}

int main()
{
int rc;
pthread_t p[2],c[2];
int i;
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

return 0;
}
