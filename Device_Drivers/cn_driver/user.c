#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#define DEVICE "/dev/time"
int main()
{
	int i,fd;
	char buf[100];

	fd=open(DEVICE,O_RDWR);
	if(fd==-1)
	{
		printf("file %s either does not exit or has been locked by another process\n",DEVICE);
		exit(-1);
	}
	scanf("%s",buf);
	write(fd,&buf,strlen(buf));
	while(1)
	{
		read(fd,&buf,sizeof(buf));
		printf("time : %s\n",buf);
		sleep(2);
	}
}
