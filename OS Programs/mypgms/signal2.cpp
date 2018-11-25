#include<signal.h>
#include<iostream>
#include<unistd.h>
#include<stdio.h>
#include<stdlib.h>
#include<err.h>
using namespace std;
static void sig_usr (int);

int main(void)
{
if (signal(SIGUSR1, sig_usr) == SIG_ERR)
{
printf("can't catch SIGUSR1");
exit(0);
}
if (signal(SIGUSR2, sig_usr) == SIG_ERR)
{
printf("can't catch SIGUSR2");
exit(0);
}
int i;
for (i=0;i<50 ;i++ )
{
pid_t pid=0;
kill(pid,SIGUSR1);
printf("waiting  ");
pause();
kill(pid,SIGUSR2);
}
}

static void sig_usr (int signo)
{
if (signo == SIGUSR1)
printf("received SIGUSR1\n");
else if (signo == SIGUSR2)
printf("received SIGUSR2\n");
else 
{
printf("received signal %d\n", signo);
exit(0);
}
}
