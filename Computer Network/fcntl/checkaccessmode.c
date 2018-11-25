#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>

int
main(void)
{
	int val;
	int fd;

	fd = open("test.txt", O_RDWR);
        //The fcntl function to obtain the file status flag
	if((val = fcntl(fd, F_GETFL, 0)) <0)
			printf("fcntl failed.\n");

	switch(val & O_ACCMODE){
	case O_RDONLY:
		printf("read only");	
		break;
	case O_WRONLY:
		printf("write only");	
		break;
	case O_RDWR:
		printf("read and write");	
		break;
	default:
		printf("unknown access mode");
	}

	if(val & O_APPEND)
			printf("append");
	if(val & O_NONBLOCK)
			printf("nonblock");


	putchar('\n');
	exit(0);
}
