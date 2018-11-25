#include<stdio.h>
#include<iostream>
using namespace std;
int main()
{
char arr[]="hello";
switch(arr)
{
case "hello":printf("okk say what u wanna to say\n");
             break;
case "hi":printf("did ur work\n");
          break;
default:printf("nothing matched\n");
             break;                       
}
}
