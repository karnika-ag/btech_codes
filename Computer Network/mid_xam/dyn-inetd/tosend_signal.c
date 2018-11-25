#include<stdio.h>
#include<sys/shm.h>
#include<sys/types.h>
#include<sys/ipc.h>
#include<signal.h>
#include<stdlib.h>  
int main()
{
int shmid1;
int *id;
key_t key=ftok(".",'d');
if((shmid1=shmget(key,sizeof(int),IPC_CREAT|0666))==-1)
{
perror("shmget error\n");
exit(0);
}
id=(int *)shmat(shmid1,NULL,0);
printf("process id is %d\n",id[0]);
kill(id[0],SIGUSR2);
}
