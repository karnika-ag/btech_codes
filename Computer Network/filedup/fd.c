#include <stdio.h>
#include <sys/types.h>
#include <dirent.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include<signal.h>
int ppid;
int pid;
int fd;
char str[50];
void parent()
{
signal(SIGUSR1,parent);
int i,n;
printf("\n1.parent:\n\n");
for(i=0;i<5;i++)
{
n=read(fd,str,18);
if(n==0)
break;
write(1,str,18);
}
if(n==0)
exit(0);
else
kill(pid,SIGUSR2);

}

void child()
{
signal(SIGUSR2,child);
int i,n;
printf("\n1.child:\n\n");
for(i=0;i<5;i++)
{
n=read(fd,str,18);
if(n==0)
break;
write(1,str,18);
}

if(n==0)
exit(0);
else
kill(ppid,SIGUSR1);

}
int main()
{

signal(SIGUSR1,parent);
signal(SIGUSR2,child);
int j,i,n;
int sin;
//sin=dup(0);
//fflush(stdin);
//int file=open("f2.txt",O_RDWR,0777);
/*if(dup2(file,0)<0)
{
perror("dup2 of main:");
exit(0);
}*/
fd=open("f2.txt",O_RDWR,0777);
printf("\nhello\n");
read(0,str,18);
write(1,str,18);
printf("kkk\n");
kill(getpid(),SIGUSR1);
pid=fork();
if(pid>0)
{

}
else if(pid==0)
{
ppid=getppid();

}
else
{
perror("forking error:");
exit(0);
}

return 0;
}
