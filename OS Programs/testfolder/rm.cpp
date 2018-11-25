#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
using namespace std;

int main(int argc,char *argv[]){
		DIR *dir=NULL;
		struct dirent *dirptr=NULL;
		char *ch;
		
		ch=getenv("PWD");
		dir=opendir(ch);
		dirptr=readdir(dir);

		if(argc==2){
			while(dirptr!=NULL){
				if(!strcmp(dirptr->d_name,argv[1]))
					{remove(dirptr->d_name);break;}
				dirptr=readdir(dir);
			}

		}

		else if(argc==3&&!strcmp(argv[1],"-i")){
			while(dirptr!=NULL){
				if(!strcmp(dirptr->d_name,argv[2])){
					cout<<"do you want to remove "<<dirptr->d_name<<" :[y/n] ? :";
					char a;
					cin>>a;
					if(a=='y'||a=='Y')
					{
						remove(dirptr->d_name);
					}
					break;
				}
				dirptr=readdir(dir);
			}
		}

		else{
			
				while(dirptr!=NULL){
					for(int i=argc-1;i>=1;i--){
						if(!strcmp(dirptr->d_name,argv[i])){
							remove(dirptr->d_name);
							break;
						}
					}
					dirptr=readdir(dir);
				}
		}
		closedir(dir);
}