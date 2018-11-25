#include <stdio.h>
#include <sys/types.h>
#include <sys/sem.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include<errno.h>
#include<error.h>
//#define SHAREDSEM "/sharedSem"

union semun {
 int val;
 struct semid_ds *buf;
 unsigned short int *array;
 };

int main()
{
 int i;
 char *shared;
 
 int sem_id=semget(1234, 2, IPC_CREAT|666);
 if(sem_id==-1)
 {
   int errst=errno;
  perror("semget error!\n");
  error(0,errno,"error in creating semget");
  if(errst==EEXIST)
{
printf("already exist");
}
  exit(1);
 }
 int shm_id=shmget(9876, 30, IPC_CREAT | 666);
 if(shm_id==-1)
 {
  perror("shmget error!\n");
  exit(1);
 }
 union semun T;
 T.val=0;
 for(i=0; i<2; i++)
 {
  if(semctl(sem_id, i,SETVAL, T)==-1)
  {
   printf("semctl error!\n");
   exit(1);
  }
 }
 if((shared=shmat(shm_id, NULL,0))==(char *)-1)
 {
  perror("shmat error!\n");
  exit(1);
 }
 int ID=fork();
 if(ID==0)
 {
  char buf[30];
   int n;
   char *tmp;
   struct sembuf tk;
  //this reads the input from console...
  while(1)
  {
    n=read(0, buf, 30);
   if(n==0)
   {
    printf("writing terminated..\n");
    break;
   }
   tmp=shared;
   strncpy(shared, buf, strlen(buf));
   tk.sem_num=0;//0-->used by this program
   tk.sem_flg=0;
   tk.sem_op=1;
   if(semop(sem_id, &tk, 1)==-1)
   {
    printf("semop error for writing!\n");
    exit(0);
   }
  }
 }
 else if(ID>0)
 {
  //takes from shared memory and writes to the console... 
  char shr[30];
  struct sembuf gh;
  while(1)
  {
   gh.sem_num=1;
   gh.sem_flg=0;
   gh.sem_op=-1;
   if(semop(sem_id, &gh, 1)==-1)
   {
    printf("semop error for reading..!\n");
    exit(1);
   }
   strncpy(shr, shared, strlen(shared));
   write(1, shr, strlen(shr));
  }
 }
 else
 {
  printf("fork error!\n");
 }
 exit(0);
}
