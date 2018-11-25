#include<stdlib.h>
#include <stdio.h>
#include <signal.h>
#include<unistd.h> 
void sigproc(int);
 
void quitproc(int); 
 
int main()
{		 
                 signal(SIGINT, sigproc);
		 signal(SIGQUIT, quitproc);
		 printf("ctrl-c disabled use ctrl-\\ to quit\n");
		 for(;;); /* infinite loop */}
 
void sigproc(int i)
{ 		 signal(SIGINT, sigproc); /*  */
		 /* NOTE some versions of UNIX will reset signal to default
		 after each call. So for portability reset signal each time */
 
		 printf("you have pressed ctrl-c \n");
}
 
void quitproc(int i)
{ 		 printf("ctrl-\\ pressed to quit\n");
		 exit(0); /* normal exit status */
}


