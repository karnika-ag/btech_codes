#include <stdio.h>
#include <sys/types.h>
#include <sys/sem.h>
#include <stdlib.h>
#include <sys/shm.h>
#include <errno.h>
#include<error.h>
#include <sys/ipc.h>
#include<pthread.h>

pthread_mutex_t mutex[5];
int active[5];

void *work(void *val)
{

int p;
p=*(int *)val;

while(1)
{
if(p%2==0)
{
pthread_mutex_lock(&mutex[p]);
pthread_mutex_lock(&mutex[(p+1)%5]);
}
else
{
pthread_mutex_lock(&mutex[(p+1)%5]);
pthread_mutex_lock(&mutex[p]);
}

active[p]=1;
printf("p %d [%d %d %d %d %d]\n",p+1,active[0],active[1],active[2],active[3],active[4]);   
sleep(2);
active[p]=0;
if(p%2==0)
{
pthread_mutex_unlock(&mutex[p]);
pthread_mutex_unlock(&mutex[(p+1)%5]);

}

else
{

pthread_mutex_unlock(&mutex[(p+1)%5]);
pthread_mutex_lock(&mutex[p]);
}

sleep(5);
}
exit(0);
}


int main()
{
int i;

for(i=0;i<5;i++)
{
 pthread_mutex_init(&mutex[i],NULL);
}

for(i=0;i<5;i++)
active[i]=0;

pthread_t pid[5];

//pthread_setconcurrency(6);

int arr[5];
for(i=0;i<5;i++)
{
arr[i]=i;
pthread_create(&pid[i],NULL,(void *)&work,(void *)&arr[i]);
}

for(i=0;i<5;i++)
pthread_join(pid[i],NULL);

}
