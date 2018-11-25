#include<pthread.h>
#include<stdio.h>
#include<stdlib.h>
#include<iostream>
using namespace std;
pthread_t oc1,oc2,oc3,oc4 ;
int prior(int [],int);
int pr[] = {3,1,2,4}; 
int turn=-1;
int comp[]={0,0,0,0};
void * func1(void * arg)
{
int y=prior(pr,4);
int t=*(int *)arg;

while(turn!=t);

int i,j ;

for(i = 0 ;i<20;i++)
 { printf("\n\n\t Function 1 started.");
   for(j=0;j<20000;j++) ;
 }
printf("\n\n\t Returning from Function 1");
comp[t]=1;
return NULL;

}



void * func2(void * arg)
{
int y=prior(pr,4);
int t=*(int *)arg;

while(turn!=t);


int i,j ;

for(i = 0 ;i<4;i++)
 { printf("\n\n\t Function 2 started.");
   for(j=0;j<20000;j++) ;
 }

printf("\n\n\t Returning from Function 2");
comp[t]=1;
return NULL;

}


void * func3(void * arg)
{
int y=prior(pr,4);
int t=*(int *)arg;

while(turn!=t);

int i,j ;
for( i = 0 ;i<10;i++)
 { printf("\n\n\t Function 3 started.");
   for(j=0;j<20000;j++) ;
 }

printf("\n\n\t Returning from Function 3");
comp[t]=1;
return NULL ;
}


void * func4(void * arg)
{
int y=prior(pr,4);
int t=*(int *)arg;

while(turn!=t);

int i,j ;

for(i = 0 ;i<7;i++)
  { printf("\n\n\t Function 4 started.");
    for(j=0;j<20000;j++) ;
 }

printf("\n\n\t Returning from Function 4");
comp[t]=1;
return NULL;

}


int prior(int ar[],int n)
{
 int i = 0 ,min , minpl ;
 min = 1000 ;

 for(i=0;i<n;i++)
  {
    if(ar[i] < min) { min = ar[i] ; minpl = (i+1) ; }    
  }

if(min < 1000) { 
turn=minpl=i-1;
if(comp[turn]==1)
ar[(minpl-1)] = 1000 ;
 return minpl ;
}
else return -1 ;

}


int main()
{
void *exit_status ; 

int y=-1,j ;
int set[]={0,1,2,3};
pthread_create(&oc1,NULL,func1,(void *)&set[0]);
pthread_create(&oc2,NULL,func2,(void *)&set[1]);
pthread_create(&oc3,NULL,func3,(void *)&set[2]);
pthread_create(&oc4,NULL,func4,(void *)&set[3]);

for(int i=0;i<4;i++)
{
int s=prior(pr,4);
for(int u=0;u<1000000;u++);
if(s==-1)
break;
}
  
printf("\n\n\t Exiting from Main");

return 0 ;


}

