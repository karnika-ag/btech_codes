#include <stdio.h>
#include <sys/types.h>
#include <dirent.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
int main()
{
char * line = NULL;
       size_t len = 0;
       ssize_t read;
int pid;
char ch;
int sin,i,j;
char str[500];
int file=open("f2.txt",O_RDONLY,0777);
if(dup2(file,0)<0)
{
perror("dup2 of main:");
exit(0);
}
for(j=0;j<2;j++)
{
pid=fork();
if(pid>0)
{
wait(pid,NULL);
printf("1parent:  \n");
for(i=0;i<2;i++)
{
if((read = getline(&line, &len, 0)) != -1) 
{
           printf("Retrieved line of length %zu :\n", read);
           printf("%s", line);
}
}
else if(pid==0)
{
printf("1child:  \n");
for(i=0;i<2;i++)
{
if((read = getline(&line, &len, 0)) != -1) 
{
           printf("Retrieved line of length %zu :\n", read);
           printf("%s", line);
}
}
exit(0);
}
else
{
perror("forking error:");
exit(0);
}
}
return 0;
}
