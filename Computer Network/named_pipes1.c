#include<stdio.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<stdlib.h>
#include<fcntl.h>
int main()
{
char *mypipe="pipe1";
mkfifo(mypipe,0666);
int fd=open(mypipe,O_RDONLY);
if(fd==-1)
{
printf("error\n");
exit(0);
}
char str[20];
read(fd,str,20);
printf("%s\n",str);
close(fd);

return 0;


}
