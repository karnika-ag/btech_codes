/* ----------------------------------------------------------------- */
/* PROGRAM  shell.c                                                  */
/*    This program reads in an input line, parses the input line     */
/* into tokens, and use execvp() to execute the command.             */
/* ----------------------------------------------------------------- */

#include <stdio.h>
#include <sys/types.h>
#include <dirent.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
 
/* ----------------------------------------------------------------- */
/* FUNCTION  parse:                                                  */
/*    This function takes an input line and parse it into tokens.    */
/* It first replaces all white spaces with zeros until it hits a     */
/* non-white space character which indicates the beginning of an     */
/* argument.  It saves the address to argv[], and then skips all     */
/* non-white spaces which constitute the argument.                   */
/* ----------------------------------------------------------------- */
int count=0;

void  parse(char *line, char **argv)
{
     count=0;
     while (*line != '\0') {       /* if not the end of line ....... */ 
          while (*line == ' ' || *line == '\t' || *line == '\n')
               *line++ = '\0';     /* replace white spaces with 0    */
          *argv++ = line; 
          count++;         /* save the argument position     */
          while (*line != '\0' && *line != ' ' && 
                 *line != '\t' && *line != '\n') 
               line++;             /* skip the argument until ...    */
     }
     *argv = '\0';     

                 /* mark the end of argument list  */
}

/* ----------------------------------------------------------------- */
/* FUNCTION execute:                                                 */
/*    This function receives a commend line argument list with the   */
/* first one being a file name followed by its arguments.  Then,     */
/* this function forks a child process to execute the command using  */
/* system call execvp().                                             */
/* ----------------------------------------------------------------- */
     
void  execute(char **argv)
{
     pid_t  pid;
     int  status;
	char s[100];     
     if ((pid = fork()) < 0) {     /* fork a child process           */
          printf("*** ERROR: forking child process failed\n");
          exit(1);
     }
     else if (pid == 0) 
	{          /* for the child process:         */
		strcpy(s,"./my");
		strcat(s,argv[0]); 
          //printf("%s\n",argv[2]);
		//printf("%s\n",s); 
		//printf("%s\n",argv[1]);
          int file;
          int current_out,tag1=0;  
          if(count>=2&&!strcmp(argv[count-2],">"))
          {

               current_out = dup(1);
               fflush(stdout);
               file = open(argv[count-1], O_CREAT | O_WRONLY, 0777);
               if(dup2(file, 1) < 0) 
               {
                  fprintf(stderr, "couldn't redirect output\n");
                  exit(1);
              }
              tag1=1;
          }  	
		if (execvp(s,argv) < 0) {     /* execute the command  */
               printf("*** ERROR: exec failed\n");
               exit(1);
          }
          if(tag1==1)
          {
               if(dup2(current_out,1) < 0) 
               {
                    fprintf(stderr, "couldn't reset output\n");
                     exit(1);
               }
          }
     }
     else {                                  /* for the parent:      */
          while (wait(&status) != pid)       /* wait for completion  */
               ;
     }
}

/* ----------------------------------------------------------------- */
/*                  The main program starts here                     */
/* ----------------------------------------------------------------- */
     
int  main()
{
     char  line[1024];             /* the input line                 */
     char  *argv[64]; 
             /* the command line argument      */
     char ch;     
     while (1) {                   /* repeat until done ....         */
          printf("Shell$");     /*   display a prompt             */
          scanf("%[^'\n']s",line);              /*   read in the command line     */
	  scanf("%c",&ch);          
	printf("\n");
          parse(line, argv);       /*   parse the line               */
          if (strcmp(argv[0], "exit") == 0)  /* is it an "exit"?     */
               exit(0);            /*   exit if it is                */
          execute(argv);           /* otherwise, execute the command */
     }
}

                

