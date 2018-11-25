#include<unistd.h>
#include<signal.h>
#include<stdio.h>
#include<stdlib.h>
#include <iostream>
void sigreceive(int i);
int main()
{
pid_t pid;
pid=fork();
if(pid==0)
{
printf("child is called\n");
signal(SIGUSR1,sigreceive);
signal(SIGKILL,sigreceive);
for(;;);
}
else
{
printf("parent sending signal to child\n");
sleep(10);
int ret=kill(pid,SIGUSR1);
printf("return value is %d\n",ret);
for(;;);
}


}

void sigreceive(int i)
{
//signal(SIGUSR1,sigreceive);
printf("child received a signal\n");
}
