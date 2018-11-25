#include <sys/socket.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <arpa/inet.h> 
#include <stdlib.h>
int sfd,nsfd,sfd1;
struct hostent *hadd;
char buffer[100];
const char* p;
void fun1()
{
   char str[BUFSIZ];
   while(1)
   {
   printf("CLIENT : enter msg \n");
     gets(str);
   write(nsfd, str, strlen(str));
   perror("write:\n");
   }
   exit(0);
 
}

void fun2()
{
   char str[BUFSIZ];
  while(1)
   {
   int n=read(nsfd,str,sizeof(str));
   str[n]='\0';
   perror("Read:\n"); 
   printf("CLIENT : received from server:- %s\n",str);
   }
  exit(0);
}

int main(int argc, char *argv[])
{
int n,size;
char smsg[2000],rmsg[2000];
struct sockaddr_in server,c1,s2,peer,remote;
if(argc!=2)
{
printf("give ip of server\n");
exit(0);
}

//hadd= gethostbyname(argv[2]);
//bcopy((char *)hadd->h_addr,(char *)&remote.sin_addr.s_addr,hadd->h_length);

//p = inet_ntop(AF_INET, &remote.sin_addr, buffer, 100);
  //  if(p != NULL)
   // {
     //   printf("Local ip is : %s \n" , buffer);
    //}
	
//printf("Hostname: %s\n", h->h_name);
//printf("IP Address: %s\n", inet_ntoa(*((struct in_addr *)h->h_addr)));     


sfd=socket(AF_INET,SOCK_STREAM,0);


if(sfd<0)
{
printf("socket not created\n");
exit(0);
}
memset(&server, '0', sizeof(server));
server.sin_family=AF_INET;
server.sin_port=htons(8888);
int rc=inet_pton(AF_INET,argv[1],&server.sin_addr);


if(rc<=0)
{
printf("inet pton error\n");
exit(0);
}


rc=connect(sfd,(struct sockaddr *)&server,sizeof(server));
if(rc<0)
{
printf("connect error\n");
exit(0);
}


else
{

 socklen_t namelen = sizeof(c1); 
 int err=getpeername(sfd,(struct sockaddr *)&peer, &namelen );
  p = inet_ntop(AF_INET, &peer.sin_addr, buffer, 100);
    printf("foreign port: %d\n", (int) ntohs(peer.sin_port));        
    if(p != NULL)
    {
        printf("foreign ip is : %s \n" , buffer);
    }


 printf("connected to s1\n");

//----------------------------------------------//

//    struct sockaddr_in c1;

     err = getsockname(sfd, (struct sockaddr*) &c1, &namelen);
         
   printf("local port: %d\n", (int) ntohs(c1.sin_port));        
   

close(sfd);
sleep(100);





//---------------------------------------------------------------//

 sfd1=socket(AF_INET,SOCK_STREAM,0);
       if(sfd1<0)
	{
	printf("socket not created\n");
	exit(0);
	}

// c1.sin_family=AF_INET;
// c1.sin_addr.s_addr=INADDR_ANY;
/* rc=inet_pton(AF_INET,p,&c1.sin_addr);
if(rc<=0)
{
printf("inet pton error\n");
exit(0);
} */
 //c1.sin_port=htons( (int) ntohs(name.sin_port)  );     
 //char *val="172.30.128.144";
 //inet_pton(AF_INET,val,&c1.sin_addr);
 rc=bind(sfd1,(struct sockaddr *)&c1,sizeof(c1));
 if(rc<0)
 {
 printf("bind failed\n");
 exit(0);
 }
 listen(sfd1,2);
 memset(&s2,'0',sizeof(s2));
 printf("bibdinfgg done\n");
 nsfd=accept(sfd1,(struct sockaddr *)&s2,&size);
 printf("everything done\n");
 if(nsfd>0)
 {
   printf("now chat with s2\n");    
           
   pthread_t thr[2];
 
   if((rc=pthread_create(&thr[0],NULL,(void *)&fun1,NULL))==-1)
   {
   perror("pthread create error\n");
   exit(0);
   }
   if((rc=pthread_create(&thr[1],NULL,(void *)&fun2,NULL))==-1)
   {
   perror("pthread create error\n");
   exit(0);
   }
   
   pthread_join(thr[0],NULL);
   pthread_join(thr[1],NULL);   
   
   
 
 }
 
 
}
return 0;
}
