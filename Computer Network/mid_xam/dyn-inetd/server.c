#include<stdio.h>
#include<string.h>  
#include<stdlib.h>  
#include<sys/socket.h>
#include<arpa/inet.h>
#include<unistd.h>   
#include<pthread.h>
#include<sys/select.h>
#include<math.h>
#include<semaphore.h>
#include<signal.h>
#include<fstream.h>
struct inetd
{
int no;
char proto[20];
int port;
char inext[20];
int limit;
char serv[20];
char wait[20];
}; 
inetd store[100];
int main()
{
ifstream fin;
fin.open("inetd_config.txt");
int i=0;
while(!fin.eof())
{
fin>>store[i].no;
cout<<store[i].no<<"\n;
fin>>store[i].proto;
cout<<store[i].proto<<"\n;
fin>>store[i].port;
cout<<store[i].port<<"\n;
fin>>store[i].inext;
cout<<store[i].inext<<"\n;
fin>>store[i].limit;
cout<<store[i].limit<<"\n;
fin>>store[i].serv;
cout<<store[i].serv<<"\n;
fin>>store[i].wait;
cout<<store[i].wait<<"\n;
}
}
