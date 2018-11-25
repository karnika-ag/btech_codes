#include <stdio.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include<stdlib.h>
#include<signal.h>
#include <unistd.h>
#include<string.h>
int csfd;
char myfifo1[12] = "ctos_fifo2";
int scfd;
char myfifo2[12] = "stoc_fifo2";
int grps[4],grpr[4];

void fun1()
{
   char str[BUFSIZ];
   while(1)
   {
   printf("CLIENT 2: enter msg \n");
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
   printf("CLIENT 2: received from server:- %s\n",str);
     for(i=1;i<=2;i++)
     {
        printf("sending ....\n");
        write(grps[i],str,strlen(str));         
     }
   sleep(2);
   }
  exit(0);
}

void fun3()
{
/*
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
*/
}

int main()
{
   csfd = open(myfifo1, O_WRONLY);
   scfd = open(myfifo2, O_RDONLY);
   int i;
   
   for(i=1;i<=2;i++)
   {
      myfifo1[10]=(char)i+'0';
      myfifo1[11]='\0';
      myfifo2[10]=(char)i+'0';
      myfifo2[11]='\0';      
      mkfifo(myfifo1,0666);
      mkfifo(myfifo2,0666);
      grps[i]= open(myfifo1, O_RDWR);
      grpr[i]= open(myfifo2, O_RDWR);
      printf("pipe%d created\n",i);
   }
   
   pthread_t thr[3];
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
   if((rc=pthread_create(&thr[2],NULL,(void *)&fun3,NULL))==-1)
   {
   perror("pthread create error\n");
   exit(0);
   }
   
   pthread_join(thr[0],NULL);
   pthread_join(thr[1],NULL);   
   pthread_join(thr[2],NULL);   
   close(csfd);
   close(scfd);


   return 0;
}
