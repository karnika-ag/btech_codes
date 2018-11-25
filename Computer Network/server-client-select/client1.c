#include <stdio.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include<stdlib.h>
#include<signal.h>
#include <unistd.h>
#include<string.h>
   int csfd;
   char *myfifo1 = "ctos_fifo1";
   int scfd;
   char *myfifo2 = "stoc_fifo1";

void fun1()
{
   char str[BUFSIZ];
   while(1)
   {
   printf("CLIENT 1: enter msg \n");
   scanf("%s", str);
   write(csfd, str, strlen(str));
 //  perror("write:\n");
   }
   exit(0);
 
}


void fun2()
{
   char str[BUFSIZ];
  while(1)
   {
   read(scfd,str,sizeof(str));
//   perror("Read:\n"); 
   printf("CLIENT 1: received from server:- %s\n",str);
  // sleep(2);
   }
  exit(0);
}
int main()
{
   csfd = open(myfifo1, O_WRONLY);
   scfd = open(myfifo2, O_RDONLY);
   pthread_t thr[2];
   int rc;
   if((rc=pthread_create(&thr[0],NULL,(void *)&fun1,NULL))==-1)
   {
   perror("pthread create error\n");
   exit(0);
   }
   if((rc=pthread_create(&thr[1],NULL,(void *)&fun2,NULL))==-1)
   {
   perror("pthread create error\n");
   exit(0);
   }
   
   pthread_join(thr[0],NULL);
   pthread_join(thr[1],NULL);   
 
   close(csfd);
   close(scfd);


   return 0;
}
