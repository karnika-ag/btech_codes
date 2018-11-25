#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#define MAX_TEXT 512

struct st
{
long int val;
char stext[MAX_TEXT];
};

int main()
{
struct st starr;
long int msgrec=0;
int running=1;
char last[4]="end";
int msgid;
msgid=msgget((key_t)1234,0666|IPC_CREAT);
if(msgid==-1)
{
printf("error in msgid\n");
exit(-1);
}


while(running)
{
if((msgrcv(msgid,(void *)&starr,MAX_TEXT,msgrec,0))==-1)
{
printf("error in receiving\n");
exit(-1);
}

if((strncmp(starr.stext,last,3))==0)
{
running=0;
}
printf("send text :  ");
printf("%s",starr.stext);
}
 if ((msgctl(msgid, IPC_RMID, 0)) == -1) 
{
      perror("msgctl(IPC_RMID) failed");
      exit(EXIT_FAILURE);
    }
return 0;
}
