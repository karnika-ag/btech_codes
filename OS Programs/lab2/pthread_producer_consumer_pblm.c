#include<stdio.h>
#include<pthread.h>

#define MAX 10
int number;
pthread_mutex_t mu=PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t sig_consumer=PTHREAD_COND_INITIALIZER;
pthread_cond_t sig_producer=PTHREAD_COND_INITIALIZER;



void producer()
{
printf("producer: \"hello i m producer # %ld  ready to produce numbers now \" \n",pthread_self());
while(1)
{
pthread_mutex_lock(&mu);
number++;
printf("producer: %d \n",number);
pthread_cond_signal(&sig_consumer);

if(number!=MAX)
pthread_cond_wait(&sig_producer,&mu);

pthread_mutex_unlock(&mu);

if(number==MAX)
{
printf("producer done...! \n");
break;
}
}
}


void consumer()
{
int printed=0;
printf("consumer: \"hello i m consumer # %ld  ready to consume numbers now \" \n",pthread_self());

while(1)
{
pthread_mutex_lock(&mu);
pthread_cond_signal(&sig_producer);
pthread_cond_wait(&sig_consumer,&mu);
printf("consumer: %d \n",number);
pthread_mutex_unlock(&mu);

if(number==MAX)
{
printf("consumer done...! \n");
break;
}
}
}




void main()
{
int rc,i;
pthread_t t[2];
number=0;
if(rc=pthread_create(&t[0],NULL,(void *)&consumer,NULL))
printf("error creating the consumer thraed..\n");
if(rc=pthread_create(&t[0],NULL,(void *)&producer,NULL))
printf("error creating the producer thraed..\n");

for(i=0;i<2;i++)
pthread_join(t[i],NULL);
printf("bone..\n");

}

