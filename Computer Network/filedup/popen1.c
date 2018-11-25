#include<stdio.h>
#include <sys/types.h>
#include <dirent.h>
#include <string.h>
#include<sys/shm.h>
#include<sys/ipc.h>

#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
int main()
{
int shmid;int *no;
if((shmid=shmget(2276,sizeof(int),IPC_CREAT|0666))==-1)
{
perror("shmget1 error\n");
exit(0);
}
no=(int *)shmat(shmid,NULL,0);
no[0]=1;
int cur_out,cur_in;
cur_out=dup(1);
cur_in=dup(0);
char buf[500];
FILE *fd=popen("./1","r");
fscanf(fd, "%100s", buf);
pclose(fd);
sleep(20);
//printf("buffer is :%s\n", buf);
//read(0,buf,sizeof(buf));
write(cur_out,buf,strlen(buf));
strcpy(buf,"hihowruimfine");
write(1,buf,strlen(buf));
return 0;
}
