#include<stdio.h>
#include<sys/shm.h>
#include<sys/sem.h>
#include<stdlib.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include<stdlib.h>
#include<signal.h>
#include <unistd.h>
int semid;
int shmid;
int *buffer;
int csfd[5];
int scfd[5];
char myfifo1[12]="ctos_fifo1";
char myfifo2[12]="stoc_fifo1";

union semun
{
int val;
struct semid_ds *buf;
unsigned short *array;
};

void semlock(int index)
{
struct sembuf temp;
temp.sem_num=index;
temp.sem_op=-1;
temp.sem_flg=0;
if((semop(semid,&temp,1))==-1)
{
perror("semop error\n");
exit(0);
}
}
void semunlock(int index)
{
struct sembuf temp;
temp.sem_num=index;
temp.sem_op=1;
temp.sem_flg=0;
if((semop(semid,&temp,1))==-1)
{
perror("semop error\n");
exit(0);
}
}

void fun(void *arg)
{
int id=*(int *)arg;
char buf[BUFSIZ];
signal(SIGUSR1,fun);
int rc;
     read(csfd[id],buf,BUFSIZ);
      if (strcmp("exit",buf)==0)
      {
         printf("Server client %d is closed\n",id);
         break;
      }

      else if (strcmp("",buf)!=0)
      {
      
         printf("SERVER :- Received from client %d : %s\n",id,buf);
         int i;
         for(i=1;i<=4 ;i++)
         {
         if(i!=id)
         {
         write(scfd[i],buf,BUFSIZ);
         printf("SERVER :- Sending to client %d \n",i);
         kill(buffer[i],SIGUSR1);
         }
         }
      }

      memset(buf, 0, sizeof(buf));
     

}


int main()
{

signal(SIGUSR1,fun);
int i,rc;
key_t key=4567;
if((semid=semget(key,5,IPC_CREAT|0666))==-1)
{
perror("semget error\n");
exit(0);
}
union semun buf;
ushort values[]={0,0,0,0,0};
buf.array=values;
if((semctl(semid,5,SETALL,buf))==-1)
{
perror("semctl error \n");
exit(0);
}

if((shmid=shmget(4567,5*sizeof(int),IPC_CREAT|0666))==-1)
{
perror("shmget error\n");
exit(0);
}

buffer=(int *)shmat(shmid,NULL,0);
buffer[0]=getpid();
semunlock(0);

 
   for(i=1;i<=4;i++)
   {  
   myfifo1[9]=(char)i+'0';
   myfifo1[10]='\0';
   myfifo2[9]=(char)i+'0';
   myfifo2[10]='\0';   
   mkfifo(myfifo1,0666);
   mkfifo(myfifo2,0666);
   csfd[i]= open(myfifo1, O_RDONLY);
   scfd[i]= open(myfifo2, O_WRONLY);
   }
   
   printf("Server started\n");
   pthread_t thr[5];
   int arr[5];

  for(i=1;i<=4;i++)
  {
  semlock(i);
  }


   for(i=1;i<=4;i++)
   {
     arr[i]=i;
     if((rc=pthread_create(&thr[i],NULL,(void *)&fun,(void *)&arr[i]))==-1)
     {
     perror("pthread error \n");
     exit(0);
     }
   }
   
	   
	for(i=1;i<=4;i++)
	{
	pthread_join(thr[i],NULL);
	}

  
   
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



