#include<stdio.h>
#include<fcntl.h>
#include<unistd.h>
#include<sys/stat.h>
int main(int argc,char *argv[])
{
int fd1,fd2;
fd1=open(argv[1],O_RDONLY);
fd2=creat(argv[2],S_IWUSR);
rename(argv[1],argv[2]);
unlink(argv[1]);
return 0;
}
