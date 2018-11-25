#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#define DEVICE "/dev/pen0"
int main()
{
	int i,fd;
	char buf[1000];

	fd=open(DEVICE,O_RDWR);
	if(fd==-1)
	{
		printf("file %s either does not exit or has been locked by another process\n",DEVICE);
		exit(-1);
	}
	scanf("%s",buf);
	write(fd,&buf,strlen(buf));
	for(i=0;i<8;i++)
	buf[i]='a';
	while(1)
	{
		read(fd,&buf,sizeof(buf));
		printf("read_frm_pendrive : %s\n",buf);
		sleep(2);
	}
}
