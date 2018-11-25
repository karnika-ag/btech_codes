#include<stdio.h>
#include<pthread.h>
#include<math.h>
#include<stdlib.h>
pthread_mutex_t no_wait,no_ace,counter;
int no_of_readers=0;
void check_and_wait_if_busy(int id);
void check_and_wait(int id);
void read(int id);
void write(int id);

void reader(void *arg)
{
int id=*((int *)arg);
printf("reader %d started \n",id);
while(1)
{
sleep(rand() % 4);
check_and_wait(id);
read(id);
}
}



void writer(void *arg)
{
int id=*((int *)arg);
printf("writer %d started \n",id);
while(1)
{
sleep(rand() % 5);
check_and_wait_if_busy(id);
write(id);
}
}

void check_and_wait_if_busy(int id)
{
if(pthread_mutex_trylock(&no_wait)!=0)
{
printf("writer %d waiting \n",id);
pthread_mutex_lock(&no_wait);


}
}


void check_and_wait(int id)
{
if(pthread_mutex_trylock(&no_wait)!=0)
{
printf("reader %d waiting \n",id);
pthread_mutex_lock(&no_wait);
}
}



void read(int id)
{
pthread_mutex_lock(&counter);
no_of_readers++;
pthread_mutex_unlock(&counter);

if(no_of_readers==1)
{
pthread_mutex_lock(&no_ace);
pthread_mutex_unlock(&no_wait);
printf("reader %d reading \n",id);
sleep(rand() % 5);
printf("reader %d finished reading \n",id);
pthread_mutex_unlock(&counter);
if(no_of_readers==0)
pthread_mutex_unlock(&no_ace);
}
}


void write(int id)
{
pthraed_mutex_lock(&no_ace);
pthread_mutex_unlock(&no_wait);
printf("writer %d writing..\n",id);
sleep(rand() % 4 +2 );
printf("writer %d finished writing",id);
pthread_mutex_unlock(&no_ace);
}

int main(int argc,char **argv)
{
pthread_t R[5],W[5];
int id[5];
for(int i=0;i<5;i++)
{
id[i]=i+1;
pthread_create(&R[i],NULL,(void *)&reader,(void *)&id[i]);
pthread_create(&W[i],NULL,(void *)&writer,(void *)&id[i]);
}
pthread_join(R[0],NULL);
exit(0);
}


