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
			
		
		//if any functionality is given

		if(argv[1][0]=='-'){
			int fun=0;
			if(!strcmp(argv[1],"-c"))
				fun=1;
			else if(!strcmp(argv[1],"-w"))
				fun=2;
			else if(!strcmp(argv[1],"-l"))
				fun=3;

					while(dirptr!=NULL){
					for(int i=argc-1;i>1;i--){
						if(!strcmp(dirptr->d_name,argv[i])){
							
							//now reading the file...

							int cc=0;
							int lc=0;
							int wc=0;
							int f=0;
							fd=open(argv[i],O_RDONLY);
							while(n=read(fd,&buf,1)>0)
							{	
								if(buf=='\n')
									lc++;
								
								else if(buf==' '&&f==0){
									
									wc++;
									f=1;
								}
								else if(buf!=' '){
									f=0;
								}
								
									cc++;
							}
                            wc++;
							cout<<"For file: "<<dirptr->d_name<<"  :  ";
							if(fun==1)
								cout<<cc<<endl;
							else if(fun==2){
								cout<<wc<<endl;
							}
							else if(fun==3)
								cout<<lc<<endl;

							break;
						}
					}
					dirptr=readdir(dir);
				}

		
		}

		//else no functionalities only files...

		else{

				while(dirptr!=NULL){
					for(int i=argc-1;i>=1;i--){
						if(!strcmp(dirptr->d_name,argv[i])){
							
							//now reading the file...

							int cc=0;
							int lc=0;

							fd=open(argv[i],O_RDONLY);
							while(n=read(fd,&buf,1)>0)
							{	
								if(buf=='\n')
									lc++;
								else
									cc++;
							}

							cout<<"For file: "<<dirptr->d_name<<"  :  "<<cc<<"  "<<lc<<endl;

							break;
						}
					}
					dirptr=readdir(dir);
				}
				
			}

			closedir(dir);	
		}
