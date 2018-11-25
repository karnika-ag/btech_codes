#include<ucontext.h>
#include<stdio.h>
#include<stdlib.h>


static ucontext_t uc_main,uc,uc2 ;

static void func1(void)
{
printf("\n\n\t Function 1 started. \n\n\t Switching Context from Function 1 to Function 2");

swapcontext(&uc,&uc2);

printf("\n\n\t Returning from Function 1");

}

static void func2(void)
{
printf("\n\n\t Function 2 started. \n\n\t Switching Context from Function 2 to Function 1");

swapcontext(&uc2,&uc);

printf("\n\n\t Returning from Function 2");

}


int main()
{

  char f1_stack[16384],f2_stack[16384] ;

  getcontext(&uc) ;

  uc.uc_stack.ss_sp = f1_stack ;
  uc.uc_stack.ss_size = sizeof(f1_stack);

  uc.uc_link = &uc_main ;

  makecontext(&uc,func1,0);


  getcontext(&uc2) ;

  uc2.uc_stack.ss_sp = f2_stack ;
  uc2.uc_stack.ss_size = sizeof(f2_stack);

  uc2.uc_link = &uc ;

  makecontext(&uc2,func2,0);

  printf("\n\n\t Swapping the context from Main to Function 2");

  swapcontext(&uc_main,&uc2);

  printf("\n\n\t Exiting from Main");

return 0 ;


}


