#include<sys/shm.h>
#include<sys/types.h>
#include<sys/ipc.h>
#include<stdio.h>
#include<stdlib.h>
#define size 5

int main()
{

int i;
int shmid,pid;
int *shm;


if((shmid=shmget(IPC_PRIVATE,size*sizeof(int),IPC_CREAT|0666))<0)
{
perror("shmget");
exit(1);
}


if((shm=(int *)shmat(shmid,NULL,0))==(int *)-1)
{
perror("shmat");
exit(1);
}


for(i=0;i<size;i++)
{
    shm[i]=0;
}


pid=fork();

if(pid==0)
{

while(1)
{
  for(i=0;i<size;i++)
{
   shm[i]++;
  printf("server inc value of %d to %d\n",i,shm[i]);
 sleep(rand()%8);
}

}

}
else if(pid>0)
{
while(1)
{
 
  for(i=0;i<size;i++)
{
    shm[i]--;
 printf("client dec value of %d to %d\n",i,shm[i]);
 sleep(rand()%12);
}
}

}
else
{
return 0;
}

exit(-1);
return 0;
}
