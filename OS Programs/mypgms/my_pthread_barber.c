#include<stdlib.h>
#include<stdio.h>
#include<pthread.h>
#define MAXCHAIRS 4
int nextcust=1;
int start=0,end=0;
int waitcust=0;
pthread_mutex_t mutex=PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t custno[MAXCHAIRS],barsleep;
int queue[MAXCHAIRS];

void barber()
{
int chair,cust;
while(1)
{

pthread_mutex_lock(&mutex);
if(waitcust==0)
pthread_cond_wait(&barsleep,&mutex);
chair=start;
cust=queue[start];
start=(start+1)%MAXCHAIRS;
waitcust--;
pthread_cond_signal(&custno[chair]);
pthread_mutex_unlock(&mutex);
printf("barber servicing %d customer\n",cust);
sleep(3);
}
exit(0);
}

void customer()
{
int chair,cust;
while(1)
{
pthread_mutex_lock(&mutex);
if(waitcust==MAXCHAIRS)
{
pthread_mutex_unlock(&mutex);
printf("customer %d leaving\n",(int)pthread_self());
sleep((time(NULL)%5)+2);
return;
}
chair=end;
cust=queue[end]=nextcust++;
end=(end+1)%MAXCHAIRS;
waitcust++;

if(waitcust==1)
pthread_cond_signal(&barsleep);
pthread_cond_wait(&custno[chair],&mutex);
pthread_mutex_unlock(&mutex);
printf("customer %d getting sericed\n",cust);
sleep(3);
}
}



int main()
{
int i;
pthread_t b,c[MAXCHAIRS+2];

pthread_create(&b,NULL,(void *)&barber,(void *)0);

for(i=0;i<MAXCHAIRS+2;i++)
pthread_create(&c[i],NULL,(void *)&customer,NULL);

for(i=0;i<MAXCHAIRS+2;i++)
pthread_join(c[i],NULL);

return 0;
}
