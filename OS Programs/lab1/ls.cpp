#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <iostream>
#include <malloc.h>
#include <string.h>
#include<unistd.h>

//#include <string>

//#include <queue>
using namespace std;
//struct stat {
//    dev_t     st_dev;     /* ID of device containing file */
//   ino_t     st_ino;     /* inode number */
//    mode_t    st_mode;    /* protection */
//    nlink_t   st_nlink;   /* number of hard links */
 //   uid_t     st_uid;     /* user ID of owner */
//    gid_t     st_gid;     /* group ID of owner */
//    dev_t     st_rdev;    /* device ID (if special file) */
//    off_t     st_size;    /* total size, in bytes */
//    blksize_t st_blksize; /* blocksize for file system I/O */
//    blkcnt_t  st_blocks;  /* number of 512B blocks allocated */
//    time_t    st_atime;   /* time of last access */
//    time_t    st_mtime;   /* time of last modification */
//    time_t    st_ctime;   /* time of last status change */
//};


using namespace std;


void recursivelist(char path[]){
	
	DIR *dir;
	DIR *dir2;
	struct dirent *dirptr;
	
	dir=opendir(path);
	
	dirptr=readdir(dir);

	while(dirptr!=NULL){
		if(dirptr->d_name[0]!='.'){
			cout<<dirptr->d_name<<"  ";
			char temp[1000];
			strcpy(temp,path);
			strcat(temp,"/");
			strcat(temp,dirptr->d_name);
			dir2=opendir(temp);

			if(dir2!=NULL){
				cout<<"files under  : "<<dirptr->d_name<<endl;
				recursivelist(temp);	
				}
			}
	dirptr=readdir(dir);
	}
}

int main(int argc,char * argv[]){
	
	DIR *dir;
	struct dirent * dirptr=NULL;

	char * ch=(char*)malloc(sizeof(char)*50);
	struct stat statbuf;
	ch=getenv("PWD");
		

		if(argc==1) dir=opendir(ch);
		//if first argument is not a directory name
		else if(argv[1][0]=='-')
		dir=opendir(ch);
	
		//if directory name is given
		else
		dir=opendir(argv[1]);

		dirptr=readdir(dir);
	
	if(argc==1){
		while(dirptr!=NULL){
			if(dirptr->d_name[0]!='.')
			printf("%s\n",dirptr->d_name);
			dirptr=readdir(dir);
		}
	}
	
	else if(!strcmp(argv[1],"-a"))
	{
	
		while(dirptr!=NULL){
			printf("%s \n ",dirptr->d_name);
			dirptr=readdir(dir);
		}
	
	}
	
	else if(!strcmp(argv[1],"-l"))
	{
	
		while(dirptr!=NULL){
			if(dirptr->d_name[0]!='.'){
			printf("%s  ",dirptr->d_name);
			stat(dirptr->d_name, &statbuf);
			cout<<statbuf.st_ctime<<"  ";
			cout<<statbuf.st_mode<<"  ";
			cout<<statbuf.st_uid<<"  ";
			cout<<endl;
		 	}
			dirptr=readdir(dir);
		}

	
	}
	
	else if(!strcmp(argv[1],"-R")){
		char *ch;
		ch=getenv("PWD");
		recursivelist(ch);
		
	}

	
	else{
			
		while(dirptr!=NULL){
			if(dirptr->d_name[0]!='.')
			printf("%s\n",dirptr->d_name);
			dirptr=readdir(dir);
		}
	
	}
}	

