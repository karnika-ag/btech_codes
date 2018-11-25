#include "onythread.cpp"
#include<stdlib.h>


static ony_t oc_main,oc,oc2 ;


// Making processes with threads , using own thread library ony_thread.h


static void func1(void)
{
printf("\n\n\t Function 1 started. \n\n\t Switching Context from Function 1 to Function 2");

onyt_switch(&oc,&oc2);

printf("\n\n\t Returning from Function 1");

}



static void func2(void)
{
printf("\n\n\t Function 2 started. \n\n\t Switching Context from Function 2 to Function 1");

onyt_switch(&oc2,&oc);

printf("\n\n\t Returning from Function 2");

onyt_restore(&oc_main);
}



int main()
{

  char f1_stack[16384],f2_stack[16384] ;


  onyt_create(&oc,func1,NULL,f1_stack,sizeof(f1_stack));


  onyt_create(&oc2,func2,NULL,f2_stack,sizeof(f2_stack));


  printf("\n\n\t Swapping the context from Main to Function 2");

  onyt_switch(&oc_main,&oc2);

  


printf("\n\nThis should be printed in main just before exiting ");

printf("\n\n\t Exiting from Main");

return 0 ;


}
