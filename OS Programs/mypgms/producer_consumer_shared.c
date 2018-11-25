#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdio.h>
#include<unistd.h>
#include<stdlib.h>

#define SHMSZ     27
char * int_tochar(int num ,char *ch);
int clearscreen();

main()
{
char c;
int shmid,pid,i,j,k,items;
key_t key;
char *shm,*s;
clearscreen();
/*
We’ll name our shared memory segment :  “5678?.
*/
key = 5678;
(void)fprintf(stderr,”nt————–  RUNNING PRODUCER CONSUMER SYSTEM ———————”);

/* Create the segment. */
if((shmid = shmget(key, SHMSZ, IPC_CREAT | 0666)) < 0)
{  perror(“shmget”);
exit(1);
}

shm=shmat(shmid,NULL,0);
shm[0]=’8';
shm[1]=’6';
shm[2]=’';

/* get a producer process */
if ((pid = fork()) < 0)
{   perror(“fork”);
exit(1);
}

if(pid==0)
{ /* producer */
i=0;
while(i<5)
{
/* Now we attach the segment to our data space.   */
if ((shm = shmat(shmid, NULL, 0)) == (char *) -1)
{   perror(“shmat”);
exit(1);
}

s = shm;
items=atoi(s);
(void)fprintf(stderr,”nntt*********** PRODUCTION ***************”);
(void)fprintf(stderr,”nt ITEMS IN STOCK : %d”,items);
(void)fprintf(stderr,”nt ITEMS PRODUCING : 3?);

/* Now put some things into the memory for the  other process to read. */
items=items+3;
shm= int_tochar(items,&s[0]);
items=atoi(shm);
(void)fprintf(stderr,”ntt ———–ITEMS IN TOTAL : %d”,items);
(void)fprintf(stderr,”ntt ————PRODUCTION COMPLETE—————–n”);
sleep(5);
++i;
}
}
else
{      /* consumer */
i=0;
while(i<5)
{
/*We need to get the segment named “5678?, created by the server. */
key = 5678;

/* Locate the segment. */
if ((shmid = shmget(key, SHMSZ, 0666)) < 0)
{    error(“shmget”);
exit(1);
}

/* Now we attach the segment to our data space.    */
if ((shm = shmat(shmid, NULL, 0)) == (char *) -1)
{    perror(“shmat”);
exit(1);
}

/* Now read what the server put in the memory.   */
s=shm;
items=atoi(s);
(void)fprintf(stderr,”nn****************CONSUMING*********************”);
(void)fprintf(stderr,”n ITEMS IN STOCK :%d”,items);
items=items-2;
(void)fprintf(stderr,”n ITEMS CONSUMING : 2 “);
s=shm;
shm=int_tochar(items,s);
/* Finally, change the memory value, indicating we have read  the segment.  */
items=atoi(shm);
(void)fprintf(stderr,”n————ITEMS IN TOTAL : %d”,items);
(void)fprintf(stderr,”n————-ITEMS CONSUMED————————-n”);
sleep(5);
++i;
}
}
exit(0);
}

char * int_tochar(int num ,char *ch)
{
int i,temp,j;
char arr[10];
for(i=1;i<5;i++)
{
temp=(int)num%(i*10);
temp=temp+48;
arr[i-1]=(char)(temp);
num=num/(i*10);
if(num==0)
break;
}
i=i-1;
for(j=0;i>=0;i–,j++)
ch[j]=arr[i];
ch[j]=’';
return ch ;
}

int clearscreen()
{   char buf[] = “clear” ;
char *args[3] ;
args[0] = buf ;
args[1]=NULL ;
int pid, status;

pid = fork();
if (pid == 0)
{
execvp(*args, args);
perror(*args);
exit(1);
}
}
