#include <sys/types.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
int main()
{
   int flags,flags1;   
   char str[500];
   
   int fd1=open("f1.txt",O_RDWR,0777);
   int fd2=open("f2.txt",O_RDWR,0777);
   int fd3=open("f3.txt",O_RDWR,0777);

   if((flags1 = fcntl(fd1,F_GETFL,0)) < 0){
    perror("fcntl: ");
   }

   
   if((flags = fcntl(fd1,F_DUPFD,7)) < 0)
   {
    perror("fcntl: ");
   }
   printf("\n %d\n", flags);
   printf("%d %d %d \n",fd1,fd2,fd3);
   printf("reading frm file1 may be\n");
   read(flags,str,sizeof(str));
   write(1,str,strlen(str));
   printf("\n-----------------------------\nreading frm file2 may be\n");
   memset(str,'\0',sizeof(str));
   read(fd2,str,sizeof(str));
   write(1,str,strlen(str));
   memset(str,'\0',sizeof(str));
   printf("\n-----------------------------\nreading frm file3 may be\n");
   read(fd3,str,sizeof(str));
   write(1,str,strlen(str));
   printf("\n-----------------------------\nreading frm file1 again may be\n");
   memset(str,'\0',sizeof(str));
   read(fd1,str,sizeof(str));
      write(1,str,strlen(str));

   
}
