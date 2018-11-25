#include<stdio.h>
#include<sys/shm.h>
#include<sys/sem.h>
#include<stdlib.h>
#include<fcntl.h>
#include<sys/stat.h>
#include<sys/types.h>
#include<sys/ipc.h>
#include<stdlib.h>
#include<signal.h>
#include<unistd.h>
int shmid,shmid1;
int *cpid;
int pid;
int csfd[5];
int scfd[5];
char myfifo1[12]="ctos_fifo1";
char myfifo2[12]="stoc_fifo1";
int *cid;
void fun()
{
signal(SIGUSR1,fun);
static int k=1;
int j,p;
char str[BUFSIZ];
while(k<=4)
{
    if(cid[k]==1)
    {
    cid[k]=0;
     read(csfd[k],str,sizeof(str));
       printf("SERVER: received from client %d: %s \n",k,str);
       for(p=1;p<=4;p++)
       {
          printf("id client%d - %d \n",p,cpid[p]);
          if(p!=k)
          {
          write(scfd[p],str,sizeof(str));
          kill(cpid[p],SIGUSR1);
          }
       }
     }          
   k=((k%4)+1);
}

}

int main()
{

signal(SIGUSR1,fun);
int i,rc;
if((shmid=shmget(2277,5*sizeof(int),IPC_CREAT|0666))==-1)
{
perror("shmget error\n");
exit(0);
}
cpid=(int *)shmat(shmid,NULL,0);


if((shmid1=shmget(3277,5*sizeof(int),IPC_CREAT|0666))==-1)
{
perror("shmget error\n");
exit(0);
}

cid=(int *)shmat(shmid1,NULL,0);


   for(i=1;i<=4;i++)
   {  
   myfifo1[9]=(char)i+'0';
   myfifo1[10]='\0';
   myfifo2[9]=(char)i+'0';
   myfifo2[10]='\0';   
   mkfifo(myfifo1,0666);
   mkfifo(myfifo2,0666);
   csfd[i]= open(myfifo1, O_RDWR);
   scfd[i]= open(myfifo2, O_RDWR);
   printf("pipe%d created\n",i);
   }
   
	 pid=getpid();
	printf("heheheeh\n");
	 printf("\nserver pid %d\n",pid);
	
	 for(i=1;i<=4;i++)
	 { 
	 printf("%d - %d   ",i,scfd[i]);
	 write(scfd[i],&pid,sizeof(pid));
	 }
 
   printf("\nServer started\n");
 
 
 
   
   while(1);
    for(i=1;i<=4;i++)
   {
    close(csfd[i]);
    close(scfd[i]);
    myfifo1[9]=i+'0';
    myfifo1[10]='\0';    
    myfifo2[9]=i+'0';
    myfifo2[10]='\0';
    unlink(myfifo1);
    unlink(myfifo2);
   }

 
 
 return 0;
 }
 
 
