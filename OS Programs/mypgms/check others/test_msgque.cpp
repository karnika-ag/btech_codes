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
int running=1;
char buffer[MAX_TEXT];
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
printf("enter text:  ");
fgets(buffer,MAX_TEXT,stdin);
if((strncmp(buffer,last,3))==0)
{
running=0;
}
starr.val=1;
strcpy(starr.stext,buffer);
if((msgsnd(msgid,(void *)&starr,MAX_TEXT,0))==-1)
{
printf("error in sending \n");
exit(-1);
}
}
return 0;
}
