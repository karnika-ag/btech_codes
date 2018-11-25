#include <stdio.h>
#include <sys/types.h>
#include <dirent.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include<sys/shm.h>
#include<sys/ipc.h>

int main()
{
int shmid;int *no;
if((shmid=shmget(2276,sizeof(int),IPC_CREAT|0666))==-1)
{
perror("shmget1 error\n");
exit(0);
}
no=(int *)shmat(shmid,NULL,0);

char buf[]="hello how r u";
write(1,buf,strlen(buf));
int cur_in=dup(0);
int cur_out=dup(1);
FILE *fd;
if(no[0]==1)
fd=popen("./2","r");
fscanf(fd,"%50s",buf);
write(cur_out,buf,strlen(buf));
return 0;
}
