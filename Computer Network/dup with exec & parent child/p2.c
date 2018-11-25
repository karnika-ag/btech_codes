#include <stdio.h>
#include <sys/types.h>
#include <dirent.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include<signal.h>
#include<sys/shm.h>
int shmid;
int *buffer;
char str[50];


void child()
{
signal(SIGUSR2,child);

int i,n;
printf("\n1.child:\n\n");
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
kill(buffer[0],SIGUSR1);

}
int main()
{

signal(SIGUSR2,child);


if((shmid=shmget(1234,sizeof(int),IPC_CREAT|0666))==-1)
{
perror("shmget error:");
exit(0);
}
buffer=(int *)shmat(shmid,NULL,0);

while(1);

return 0;
}
