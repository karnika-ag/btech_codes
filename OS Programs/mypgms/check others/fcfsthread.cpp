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


int main()
{

  void *exit_status ; 

  pthread_create(&oc1,NULL,func1,NULL);
  pthread_join(oc1,&exit_status);

 printf("\n\n\t End of process 1 ");

  pthread_create(&oc2,NULL,func2,NULL);
  pthread_join(oc2,&exit_status);

 printf("\n\n\t End of process 2 ");


  pthread_create(&oc3,NULL,func3,NULL);
  pthread_join(oc3,&exit_status);

 printf("\n\n\t End of process 3 ");


  pthread_create(&oc4,NULL,func4,NULL);
  pthread_join(oc4,&exit_status);

 printf("\n\n\t End of process 4 ");

  
printf("\n\n\t Exiting from Main");

return 0 ;


}

