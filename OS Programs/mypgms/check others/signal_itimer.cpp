#include<stdio.h>
#include<signal.h>
#include<iostream>
using namespace std;
void sighandler(int i)
{
static int tt=0;
signal(SIGALRM,sighandler);
if(tt= !tt)
cout<<"tick\n";
else
cout<<"tock\n";
}

int main()
{

signal(SIGALRM,sighandler);

for(int i=0;i<20;i++)
{
alarm(1);
pause();
}

return 0;
}

