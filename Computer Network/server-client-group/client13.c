#include <stdio.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include<stdlib.h>
#include<signal.h>
#include <unistd.h>
#include<string.h>
int csfd;
char myfifo1[12] = "ctos_fifo1";
int scfd;
char myfifo2[12] = "stoc_fifo1";
int grps[4],grpr[4];
/*
void fun1()
{
   char str[BUFSIZ];
   while(1)
   {
   printf("CLIENT 1: enter msg \n");
   scanf("%s", str);
   write(csfd, str, strlen(str));
   perror("write:\n");
   sleep(2);
   }
   exit(0);
 
}

void fun2()
{
   int i;
   char str[BUFSIZ];
  while(1)
   {
   read(scfd,str,sizeof(str));
   perror("Read:\n"); 
   printf("CLIENT 1: received from server:- %s\n",str);
   for(i=0;i<2;i++)
   {
             
   }
   sleep(2);
   }
  exit(0);
}
*/

void fun3()
{
char str[500];
printf("entered..\n");
   while(1)
   {
       read(grpr[2],str,sizeof(str));
       perror("read:");
       printf("%s\n",str);     
   }
}

int main()
{
// csfd = open(myfifo1, O_WRONLY);
//   scfd = open(myfifo2, O_RDONLY);
   
   int i;
   for(i=1;i<=2;i++)
   {
      myfifo1[10]=(char)i+'0';
      myfifo1[11]='\0';
      myfifo2[10]=(char)i+'0';
      myfifo2[11]='\0';     
      grpr[i]= open(myfifo1, O_RDWR);
      grps[i]= open(myfifo2, O_RDWR);
      printf("pipe%d created\n",i);         
   }
 /*  pthread_t thr[2];
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
*/
   fun3();
 return 0;
}
