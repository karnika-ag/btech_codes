 #include<stdio.h>  
 #include<unistd.h>  
 #include<string.h> 
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/wait.h>
#include<stdlib.h>
 int main()  
 {  
// www.c-madeeasy.blogspot.com 
   int pid1[2];
   char str[50];
   pipe(pid1);
   int pid;
   while(1)
   {
   pid=fork();
   if(pid==0)
   {
     sleep(5);
     printf("received somethng\n");
     //close(pid1[1]);
     read(pid1[0],str,sizeof(str));
     printf("%s\n",str);
     exit(0);
   }
   else
   {
     printf("enter string\n");
     scanf("%s",str);
     // sleep(5);
     //for(int i=0;i<100;i++)
     //printf("%d ",i);
     //close(pid1[0]);
     write(pid1[1],str,sizeof(str));
     printf("%s\n",str);
     waitpid(pid,NULL,0);
      printf(" hello \n");
     }
   }
   printf("i m out\n");
   // wait(2);
  return 0;
 }  
