#include <sys/wait.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>
#include <string>
#include <iostream>
#include <stdlib.h>
#include <dirent.h>
#include <stdio.h>
#include <fcntl.h>
#include <sys/param.h>
#include <sys/signal.h>
#include <sys/syscall.h>
#include <sys/procfs.h>
using namespace std;
int ParseArg(char* cmnd, char* cmd[], char input[])
{

        cout << "shell> ";
        cin.getline(input,50);
    	cmnd = strtok(input, " ");
    	int i = 0;
    	int flag=0;
    	while(cmnd != NULL)
   	{
        	cmd[i] = cmnd;
       		i++;

       		if(!strcmp(cmd[i-1],"<")||!strcmp(cmd[i-1],">"))
       			flag=1;
        	cmnd = strtok(NULL, " ");
    	}
    	return flag;
}

void Clean(char* cmd[])
{
        for(int a=0; a < 40; a++)
	{
             cmd[a] = NULL;
        }
}

void Execute(char* cmd[] , int flag)
{
	 pid_t pid;
    pid = fork();
    switch(pid)
    {
        case -1: 
            cout << "DEBUG:Fork Failure" << endl;
            exit(-1);
        case  0:
        if(!flag)
            execvp(cmd[0], cmd);
        else{
        	char * ch=(char *)malloc(sizeof(char)*100);
        	strcpy(ch,cmd[0]);
        	for(int i=1;cmd[i]!=NULL;i++)
        	{	strcat(ch," ");
        		strcat(ch,cmd[i]);
        	}
        	
/* in = open("input",O_RDONLY);
dup2(in,STDIN_FILENO);
close(in);
out = open("output",O_WRONLY|O_CREAT,0666); // Should also be symbolic values for access rights
dup2(out,STDOUT_FILENO);
close(out);
execlp("sort","sort",NULL);
*/			int k=0;
		for(k=0;cmd[k]!=NULL;k++){
			if(!strcmp(cmd[k],"<")||!strcmp(cmd[k],">"))
       			break;
       		}

				int out = open(cmd[k+1],O_WRONLY|O_CREAT,0666); // Should also be symbolic values for access rights
				dup2(out,STDOUT_FILENO);
				close(out);
				cmd[k]=NULL;
        	execvp(cmd[0],cmd);
        	execlp(cmd[0],cmd[0],NULL);
        }

        default: 
            wait(NULL);
            cout << "DEBUG:Child Finished" << endl;
    }
}

int main()
{
   char* cnd;
   char* cmd[40];
   char input[50];
   int flag=0;
   while(cmd[0] != NULL)
   {
        
        Clean(cmd);
    	flag=ParseArg(cnd, cmd, input);
    	//cout<<flag<<"  \n";
    	//cin.getline(cmd);
    	if(strcmp(cmd[0], "exit") == 0 || strcmp(cmd[0], "quit") == 0 )
    	{
             break;
    	}
    	else
    	{
            Execute(cmd,flag);
    	}
   }
   return 1;
}

