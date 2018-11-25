#include<stdio.h>
#include<unistd.h>
#include<fcntl.h>
#include<dirent.h>
#include<ucontext.h>
#include<sys/types.h>
#include<sys/stat.h>

typedef struct ony_st { ucontext_t uc; } ony_t ;

#define onyt_save(onyt) (void) getcontext( &(onyt) -> uc) 

#define onyt_restore(onyt) (void) setcontext( &(onyt) -> uc) 

#define onyt_switch(onyt_o,onyt_n) (void) swapcontext( &((onyt_o) -> uc), &((onyt_n) -> uc) )


void onyt_create( ony_t *onyt , void (*sf_addr) (void *), void *sf_arg, void *sk_addr, size_t sk_size )
{


getcontext( &(onyt->uc)) ;


onyt -> uc.uc_link = NULL ;
onyt -> uc.uc_stack.ss_sp = sk_addr ;
onyt -> uc.uc_stack.ss_size = sk_size ;
onyt -> uc.uc_stack.ss_flags = 0 ;

makecontext(&(onyt -> uc),sf_addr,1,sf_arg);
return ;
}


void ony_join(ony_t *tid , void * alt)
{

sleep(5) ;

} 

