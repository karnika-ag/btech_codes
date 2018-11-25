#include<stdio.h>
#include<stdlib.h>
#include<ucontext.h>
#include<unistd.h>
#define timeslice 2
static ucontext_t uc_main,uc1,uc2,uc3,uc4;
int BT[]={5,3,2,4};

void process1(void)
{
int i;
int count=timeslice;

for(i=0;i<BT[0];i++)
{
printf(" \n function 1 running ");
sleep(1);
count--;
if(!count)
{
  count=timeslice;
  swapcontext(&uc1,&uc2);
}
}

while(1)
swapcontext(&uc1,&uc2);
}


void process2(void)
{
int i;
int count=timeslice;

for(i=0;i<BT[1];i++)
{
printf(" \n function 2 running ");
sleep(1);
count--;
if(!count)
{
  count=timeslice;
  swapcontext(&uc2,&uc3);
}
}

while(1)
swapcontext(&uc2,&uc3);
}


void process3(void)
{
int i;
int count=timeslice;

for(i=0;i<BT[2];i++)
{
printf(" \n function 3 running ");
sleep(1);
count--;
if(!count)
{
  count=timeslice;
  swapcontext(&uc3,&uc4);
}
}

while(1)
swapcontext(&uc3,&uc4);
}



void process4(void)
{
int i;
int count=timeslice;

for(i=0;i<BT[3];i++)
{
printf(" \n function 4 running ");
sleep(1);
count--;
if(!count)
{
  count=timeslice;
  swapcontext(&uc4,&uc1);
}
}

while(1)
swapcontext(&uc4,&uc1);

}

int main()
{
char stack1[16384],stack2[16384],stack3[16384],stack4[16384],stack5[16384];
getcontext(&uc1);
uc1.uc_stack.ss_sp=stack1;
uc1.uc_stack.ss_size=sizeof(stack1);
uc1.uc_link=&uc_main;
makecontext(&uc1,process1,0);

getcontext(&uc2);
uc2.uc_stack.ss_sp=stack2;
uc2.uc_stack.ss_size=sizeof(stack2);
uc2.uc_link=&uc_main;
makecontext(&uc2,process2,0);


getcontext(&uc3);
uc3.uc_stack.ss_sp=stack3;
uc3.uc_stack.ss_size=sizeof(stack3);
uc3.uc_link=&uc_main;
makecontext(&uc3,process3,0);

getcontext(&uc4);
uc4.uc_stack.ss_sp=stack4;
uc4.uc_stack.ss_size=sizeof(stack4);
uc4.uc_link=&uc_main;
makecontext(&uc4,process4,0);

swapcontext(&uc_main,&uc1);
printf("exiting main....");

}


