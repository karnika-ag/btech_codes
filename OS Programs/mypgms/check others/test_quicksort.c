#include<stdio.h>
//#include<iostream>
//using namespace std;
#include<pthread.h>
#define maxsub 20
#define minsub 2

struct sublist
{
int start;
int end;
};
struct sublist sublist_info[maxsub];
int N,P;
int args[64];
int A[2000];
pthread_barrier_t barr;
pthread_cond_t full,empty;
pthread_mutex_t mut;
int sleepcount,sort_comp;
int head=0,tail=0;

void insert_sublist(int start,int end)
{
pthread_mutex_lock(&mut);

while(((tail+1)%maxsub)==head)
{
pthread_cond_wait(&empty,&mut);
}
sublist_info[tail].start=start;
sublist_info[tail].end=end;
tail=(tail+1)%maxsub;

pthread_cond_signal(&full);
pthread_mutex_unlock(&mut);

}

struct sublist remove_sublist()
{
  struct sublist retval;
 pthread_mutex_lock(&mut);
 while((head==tail) && (!sort_comp))
{
sleepcount++;
if(sleepcount<P)
{
 pthread_cond_wait(&full,&mut);
sleepcount--;
}
else
{
			sort_comp = 1;
			pthread_cond_broadcast(&full);
}

}
if (sort_comp == 0)
	{
		retval = sublist_info[head];
		head = (head + 1) % maxsub;		

		//if (top == MAXSUBLISTS - 1)
		pthread_cond_signal(&empty);
	}
	else
	{
		retval.start = 0;
		retval.end = 0;
	}

pthread_mutex_unlock(&mut);
return retval;
 
}

void insertionsort(int start,int end)
{
int i,j,val;
for(i=start+1;i<=end;i++)
{
j=i-1;
val=A[i];
while(j>=start && A[j]>val)
{
A[j+1]=A[j];
j--;
}
A[j+1]=val;
}
}

int partition(int start,int end)
{
int i,j,pivotpos;
int pivot=A[end];
i=start;
j=end-1;
int done=0;int temp;
while(!done)
{
	while(i<j && A[i]<pivot) i++;
	while(i<j && A[j]>pivot) j--;
	if(i<j)
	{
	temp=A[i];
	A[i]=A[j];
	A[j]=temp;
	}
	else
	{
	 if(A[i]>pivot)
	{
	A[end]=A[i];
	A[i]=pivot;
	pivotpos=i;
	}
	else pivotpos=end;
	done=1;
	}
}
return pivotpos;
}
void quicksort(int start,int end)
{
int i,n,pivot;
int lo,hi;
quicksort_1:
if(end<=start)return;
if(end-start+1<minsub)
{
insertionsort(start,end);

}

else
{
pivot=partition(start,end);
if(pivot-1>start && pivot+1<end)
{
                   if ((pivot-start-1) < (end - pivot - 1))
			{
				insert_sublist(start, pivot-1); 
				start = pivot+1;
				goto quicksort_1;
			}
			else
			{
				insert_sublist(pivot+1, end); 
				end = pivot-1;
				goto quicksort_1;
			}
}
else if(pivot-1>start)
{
end = pivot-1;
goto quicksort_1;
}
else if(pivot+1<end)
{
start=pivot+1;
goto quicksort_1;
}
else
{
printf("Both sublists wont exist! Should not happen!\n");
}
}

}

void *thread_func(void *arg)
{
int t=*(int *)arg;
struct sublist sub;
int done=0;

pthread_barrier_wait(&barr);
printf("Thread id : %d \n",t);
if(arg==0)
{
  sub.start=0;
  sub.end=N-1;
}
else
sub=remove_sublist();

do
{
if(sub.start==0 && sub.end==0)done=1;
else
{
quicksort(sub.start,sub.end);
sub=remove_sublist();
}
}while(done!=1);
printf("Terminating the thread function\n");
	return NULL;

}






int main(int argc,char *argv[])
{

int i,j;
int t1,t2,t3,t4;
int t;
pthread_t thr[64];
if(argc!=3)
{
printf("error less argument\n");
exit(-1);
}

P=atoi(argv[1]);
N=atoi(argv[2]);

pthread_barrier_init(&barr,NULL,P);
pthread_cond_init(&full,NULL);
pthread_cond_init(&empty,NULL);
pthread_mutex_init(&mut,NULL);
sleepcount=0;
sort_comp=0;

for(i=0;i<64;i++)args[i]=i;


for(i=0;i<2000;i++)A[i]=i;

j=1137;

for(i=0;i<N;i++)
{
int temp=A[i];
A[i]=A[j];
A[j]=temp;
j=(j+337)%N;
}
for(i=0;i<N;i++)
printf(" %d ",A[i]);
printf("\n");

t1 = time(NULL);	
	for (i=1; i<P; i++)
		pthread_create(&thr[i], NULL, thread_func, &args[i]);
	t2 = time(NULL);	
	thread_func(&args[0]);
	t3 = time(NULL);	
	
	for (i=1; i<P; i++)
		pthread_join(thr[i], NULL);

	t4 = time(NULL);	

	printf("\nTime elapsed : creation %d, sort : %d, joining : %d\n",t2-t1, t3-t2, t4-t3);

for(i=0;i<N;i++)
printf(" %d ",A[i]);
	return 0;




}
