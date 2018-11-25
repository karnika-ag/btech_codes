#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<stdio.h>  
#include<unistd.h>  
#include<string.h> 
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/wait.h>
#include<stdlib.h>
#include<stdio.h> 

int main()
{
int i,pid;
printf("i m in main\n");
pid=fork();
if(pid>0)
{
printf("i m in parnt\n");
i+=5;
printf("parent 2 executing\n");
exit(0);
}

else if(pid==0)
{
printf("child executing\n");
 i+=7;
execve("abc",NULL,NULL);
printf("child after executing\n");
}
else
{
printf("error");
}
}
