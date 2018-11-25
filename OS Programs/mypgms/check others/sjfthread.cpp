#include<pthread.h>
#include<stdio.h>
#include<stdlib.h>

pthread_t oc1,oc2,oc3,oc4 ;

void * func1(void * arg)
{
int i,j ;

for(i = 0 ;i<20;i++)
 { printf("\n\n\t Function 1 started.");
   for(j=0;j<20000;j++) ;
 }
printf("\n\n\t Returning from Function 1");

return NULL;

}



void * func2(void * arg)
{

int i,j ;

for(i = 0 ;i<4;i++)
 { printf("\n\n\t Function 2 started.");
   for(j=0;j<20000;j++) ;
 }

printf("\n\n\t Returning from Function 2");

return NULL;

}


void * func3(void * arg)
{
int i,j ;
for( i = 0 ;i<10;i++)
 { printf("\n\n\t Function 3 started.");
   for(j=0;j<20000;j++) ;
 }

printf("\n\n\t Returning from Function 3");

return NULL ;
}


void * func4(void * arg)
{
int i,j ;

for(i = 0 ;i<7;i++)
  { printf("\n\n\t Function 4 started.");
    for(j=0;j<20000;j++) ;
 }

printf("\n\n\t Returning from Function 4");

return NULL;

}


int burst(int ar[],int n)
{
 int i = 0 ,min , minpl ;
 min = 10000 ;

 for(i=0;i<n;i++)
  {
    if(ar[i] < min) { min = ar[i] ; minpl = (i+1) ; }    
  }

if(min < 10000) { ar[(minpl-1)] = 10000 ; return minpl ;}
else return -1 ;

}


int main()
{

  void *exit_status ; 
int br[] = {20,4,10,7}; int y=-1,j ;

for(j=0;j<4;j++)
{
   y = burst(br,4);

  if(y == -1) break ;

 if(y==1)
{
  pthread_create(&oc1,NULL,func1,NULL);
  pthread_join(oc1,&exit_status);

 printf("\n\n\t End of process 1 ");
}

if(y==2)
{
  pthread_create(&oc2,NULL,func2,NULL);
  pthread_join(oc2,&exit_status);

 printf("\n\n\t End of process 2 ");
}
if(y==3)
{
  pthread_create(&oc3,NULL,func3,NULL);
  pthread_join(oc3,&exit_status);

 printf("\n\n\t End of process 3 ");

}

if(y==4)
{
  pthread_create(&oc4,NULL,func4,NULL);
  pthread_join(oc4,&exit_status);

 printf("\n\n\t End of process 4 ");

}


}
  
printf("\n\n\t Exiting from Main");

return 0 ;


}


