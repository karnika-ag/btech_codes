#include<unistd.h>
#include<signal.h>
#include<stdio.h>
#include<stdlib.h>
#include <iostream>
using namespace std;
int main()
{
void tictoc(int);
int i;
signal(SIGALRM,tictoc);
for(i=0;i<20;i++)
{
alarm(1);
pause();
}

}

void tictoc(int i)
{
static int tt=0;
signal(SIGALRM,tictoc);
if(tt= !tt)
cout<<"tick\n";
else
cout<<"tock\n";
}
