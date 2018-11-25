#include <stdio.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include<stdlib.h>
#include<signal.h>
#include<sys/shm.h>
#include<sys/ipc.h>
#include<signal.h>
#include <unistd.h>
#include<string.h>
int shmid;
int *no;
int p;
int csfd;
char myfifo1[12] = "ctos_fifo1";
int scfd;
char myfifo2[12] = "stoc_fifo1";

void fun1()
{
   char str[BUFSIZ];
   while(1)
   {
   printf("CLIENT %d: enter msg \n",p);
   scanf("%s", str);
   write(csfd, str, strlen(str));
   perror("write:\n");
   }
   exit(0);
 
}

void fun2()
{
   char str[BUFSIZ];
  while(1)
   {
   read(scfd,str,sizeof(str));
   perror("Read:\n"); 
   printf("CLIENT 1: received from server:- %s\n",str);
  // sleep(2);
   }
  exit(0);
}
int main()
{

printf("starting...........\n");
if((shmid=shmget(2274,sizeof(int),IPC_CREAT|0666))==-1)
{
perror("shmget error\n");
exit(0);
}
   no=(int *)shmat(shmid,NULL,0);
   no[0]++;
   printf(".....  %d  ......\n",no[0]);
   p=no[0];
   printf(".....  %d  ......\n",p);

   myfifo1[9]=(char)p+'0';
   myfifo1[10]='\0';
   printf("%s\n",myfifo1);
   myfifo2[9]=(char)p+'0';
   myfifo2[10]='\0';   
   printf("%s\n",myfifo2);
   printf("happy\n");
   mkfifo(myfifo1,0666);
   mkfifo(myfifo2,0666);
   
   csfd = open(myfifo1, O_RDWR);
   scfd = open(myfifo2, O_RDWR);
   
//   kill(no[1],SIGUSR1);
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
