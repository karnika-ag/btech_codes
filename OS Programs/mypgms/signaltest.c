#include<stdio.h>
#include<signal.h>
#include<unistd.h>
#include<stdio.h>
#include<stdlib.h>

void sighandler(int signo)
{
	printf("%d signal recieved\n",signo);
	exit(0);
}

int main()
{
	pid_t pid;
	pid = fork();
	if(pid > 0)
	{
		printf("parent\n");
		printf("pid is %d\n",pid);
		printf("Enter PID: ");
		scanf("%d",&pid);
		sleep(10);
		kill(pid,SIGALRM);
		perror("kill:");
		while(1);
	}
	else
	{
		
		printf("child at %d\n",getpid());
		//alarm(1);
		signal(SIGALRM,sighandler);
		perror("signal");
		
		while(1);
	}
	return 0;
}
