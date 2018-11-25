#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <unistd.h>
using namespace std;

int main(int argc,char *argv[]){
		DIR *dir=NULL;
		struct dirent *dirptr=NULL;
		char *ch;
		char buf;
		int fd;
		int n;
		
		ch=getenv("PWD");
		dir=opendir(ch);
		dirptr=readdir(dir);
			
				while(dirptr!=NULL){
					for(int i=argc-1;i>=1;i--){
						if(!strcmp(dirptr->d_name,argv[i])){
							
							//now reading the file...

							fd=open(argv[i],O_RDONLY);
							while(n=read(fd,&buf,1)>0)
								cout<<buf;

							
						}
					}
					dirptr=readdir(dir);
				}
				closedir(dir);
		}
