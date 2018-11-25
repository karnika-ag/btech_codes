#include<iostream>
using namespace std;
class stack
{
      private:
              int a[10];
              int top;
      public:
             stack();
             void push(int);
             int pop();
};
stack::stack()
{
  top=-1;
}
void stack::push(int n)
{
     if(top==10)
     cout<<"\nstack is full\n";
     else
     a[++top]=n;
}
int stack::pop()
{
    if(top==-1)
    cout<<"\nstack is empty\n";
    return a[top--];
}


int main()
{
stack s;
int y,n;
do
{
    cout<<"\npress 1 to push 2 to pop 3 to terminate\n";
    cout<<"enter ur choice\n";
    cin>>y;
    switch(y)
    {
      case 1: cout<<"enter the no. to be pushed\n";
        cin>>n;
        s.push(n);
        break;
      case 2:
           cout<<"element popped is "<<s.pop();
           break;
      case 3:
           break;
    }
}while(y!=3);
system("pause");
return 0;
}
