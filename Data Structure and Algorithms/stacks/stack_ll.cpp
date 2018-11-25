#include<iostream>
using namespace std;
class stack
{
 private:
         struct node
         {
                int data;
                node *right;
          }*top,*p;
public:
       stack();
       void push(int n);
       void pop();
};
stack::stack()
{
 top=NULL;
}
void stack::push(int n)
{
     if(top==NULL)
     {
                  p=new node;
                  p->data=n;
                  p->right=top;
                  top=p;
     }
     else
     {
         node *r=new node;
         r->data=n;
         r->right=top;
         top=r;
     }
}
void stack::pop()
{
     if(top==NULL)
     cout<<"stack is empty\n";
     else
     {
         node *temp=top;
         cout<<"element deleted is :"<<temp->data<<"\n";
         top=top->right;
         delete temp;
     }
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
           s.pop();
           break;
      case 3:
           break;
    }
}while(y!=3);
system("pause");
return 0;
}
