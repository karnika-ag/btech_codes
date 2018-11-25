#include <stdio.h>
#include <sys/types.h>
#include <dirent.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
int main()
{
int pid;
int sout;
char str[50];
sout=dup(1);
fflush(stdout);
int file=open("f2.txt",O_RDWR,0777);
if(dup2(file,1)<0)
{
perror("dup2 of main:");
exit(0);
}

scanf("%[^\n]%*c",str);
write(1,str,strlen(str));

pid=fork();
if(pid>0)
{
printf("parent:\n\n");
scanf("%[^\n]%*c",str);
write(1,str,strlen(str));
wait(pid,NULL);
}
else if(pid==0)
{
printf("child:\n\n");
scanf("%[^\n]%*c",str);
write(1,str,strlen(str));
exit(0);
}
else
{
perror("forking error:");
exit(0);
}

return 0;
}
