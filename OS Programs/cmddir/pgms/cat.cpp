#include<fcntl.h>
#include<stdio.h>
#include<unistd.h>
int main(int argc,char *argv[])
{
int fd,n;
char buf;
fd=open(argv[1],O_RDONLY);
printf("contents of %s file are ",argv[1]);
while((n=read(fd,&buf,1))>0)
{
write(1,&buf,1);
}
return 0;
}
