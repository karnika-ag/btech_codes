#include <stdio.h>
#include <sys/types.h>
#include <dirent.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include<signal.h>
#include<sys/shm.h>
int ppid;
int pid;
int shmid;
int *buffer;
char str[50];
void parent()
{
signal(SIGUSR1,parent);
int i,n;
printf("\n1.parent:\n\n");
for(i=0;i<5;i++)
{
n=read(0,str,18);
if(n==0)
break;
write(1,str,18);
}
if(n==0)
exit(0);
else
kill(pid,SIGUSR2);

}
int main()
{

signal(SIGUSR1,parent);

if((shmid=shmget(1234,sizeof(int),IPC_CREAT|0666))==-1)
{
perror("shmget error:");
exit(0);
}
buffer=(int *)shmat(shmid,NULL,0);
buffer[0]=getpid();
int j,i,n;
int sin;
sin=dup(0);
fflush(stdin);
int file=open("f2.txt",O_RDWR,0777);
if(dup2(file,0)<0)
{
perror("dup2 of main:");
exit(0);
}
printf("\nhello\n");
read(0,str,18);
write(1,str,18);
printf("\nNOW FORKING\n");
pid=fork();

if(pid>0)
{

sleep(10);
kill(pid,SIGUSR2);
while(1);
}
else if(pid==0)
{

execv("abc",0);

}
else
{
perror("forking error:");
exit(0);
}

return 0;
}
