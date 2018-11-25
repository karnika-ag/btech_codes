#include<stdio.h>
#include<iostream>
#include<math.h>
#include<string.h>
#include<unistd.h>
#include<stdio.h>
#include<stdlib.h>
using namespace std;
#include<pthread.h>
int N,P;
int ele[64] = { 1 , 2 , 3 , 4 , 5 , 6 , 7 , 8 , 9 , 10, 11, 12, 13, 14, 15,
                16, 17, 18, 19 ,20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31,
                32, 33, 34, 35, 36, 37, 38, 39, 40, 41, 42, 43, 44, 45, 46, 47,
                48, 49, 50, 51, 52, 53, 54, 55, 56, 57, 58, 59, 60, 61, 62, 63,64};

pthread_mutex_t mut;
pthread_barrier_t barr;
int sum=0;

void *mmalt(void *arg)
{
int t=*(int *)arg;
int start=(t*N)/P;
int end=((t+1)*N)/P;
int partialsum=0;
pthread_barrier_wait(&barr);
printf("thraed starting \n");
for(int i=start;i<end;i++)
{
 partialsum+=ele[i];
}

pthread_mutex_lock(&mut);
sum+=partialsum;
pthread_mutex_unlock(&mut);

return NULL;

}
int main(int argc,char *argv[])
{
int t1,t2,t3,t4;
pthread_t thr[64];
pthread_mutex_init(&mut,NULL);
int arr[64];
arr[0]=0;
if(argc!=3)
{
printf("need more arguments \n");
exit(-1);
}
N=atoi(argv[1]);
P=atoi(argv[2]);

printf(" n nad p %d %d \n",N,P);
pthread_barrier_init(&barr,NULL,P);
t1=time(NULL);
for(int i=1;i<P;i++)
{
arr[i]=i;
pthread_create(&thr[i],NULL,mmalt,&arr[i]);
}
t2=time(NULL);
mmalt(&arr[0]);
t3=time(NULL);
for(int i=1;i<P;i++)
{
pthread_join(thr[i],NULL);
}
t4=time(NULL);

printf("Time for completion : creation %d, reduction : %d, joining : %d sum is %d \n",t2-t1, t3-t2, t4 - t3,sum);
	return 0;

}
