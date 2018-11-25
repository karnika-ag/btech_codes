#include<semaphore.h>
#include<pthread.h>
#include<stdio.h>
void *producer(void *);
void *consumer(void *);
int append();
int take();

sem_t s ;
sem_t n ;
sem_t e ;
int bsize[5],sh_var=5,cnt=0,j,i,w;
int in=0,out=0;
pthread_t p[3],c;

void *producer(void *i)
{
printf("\n-------------------------------------");
printf("\n\nProducer %d is producing",i);
cnt++;
printf("\nnew incoming value : %d",sh_var);
sem_wait(&e);
sem_wait(&s);
append();
printf("\nbuffer values\n");
for(j=0;j<4;j++)
{
printf("\t%d",bsize[j]);
}
sem_post(&s);
sem_post(&n);
}

void * consumer(void *i)
{
printf("\n-------------------------------------");
printf("\n\nconsumer %d is consuming",i);
sem_wait(&n);
sem_wait(&s);
take();
printf("\n buffer values:\n");
for(j=4;j>0;j--)
{
printf("\t%d",bsize[j]);
}printf("\n-------------------------------------");

sem_post(&s);
sem_post(&e);
consume();
}

int consume()
{
cnt--;
printf(":",cnt);
printf("\nvalue consumed");
}

int take()
{
    w = bsize[out];
    bsize[out]=0;
    out = (out + 1)%5;
    return(0);
}

int append()
{
    bsize[in]=sh_var;
    sh_var++;
    in=(in+1)%5;
       
    if(in==4)
    {
    in=0;
    }
    return(0);
}

int main()
{

sem_init(&e,0,4);
sem_init(&n,0,0);
sem_init(&s,0,1);

pthread_create(&p[0],NULL,(void *)producer,(void *)0);
pthread_create(&c,NULL,(void *)consumer,(void *)0);
pthread_create(&p[1],NULL,(void *)producer,(void *)1);
pthread_create(&p[2],NULL,(void *)producer,(void *)2);
pthread_create(&p[2],NULL,(void *)producer,(void *)3);
pthread_create(&p[2],NULL,(void *)producer,(void *)4);
pthread_create(&p[2],NULL,(void *)producer,(void *)5);

pthread_join(p[0],NULL);
pthread_join(c,NULL);
pthread_join(p[1],NULL);
pthread_join(p[2],NULL);
sem_destroy(&n);
sem_destroy(&s);
return(0);
}

