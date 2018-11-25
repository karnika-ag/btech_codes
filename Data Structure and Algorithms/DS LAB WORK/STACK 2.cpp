#include<iostream>
using namespace std;
class stack
{
 private:
         struct node
         {
                int data;
                node *link;
          }*top,*p;
public:
       stack();
       void push(int n);
       void pop();
       void display();
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
                  p->link=top;
                  top=p;
     }
     else
     {
         node *r=new node;
         r->data=n;
         r->link=top;
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
         top=top->link;
         delete temp;
     }
}      
void stack::display()
{
     if(top==NULL)
     {
                  cout<<"stack is empty\n";
                  }
                  else
                  {
                     struct node *temp;
                      temp=top;
                      while(temp->link!=NULL)
                      {
                                       cout<<temp->data<<"\n";
                                       temp=temp->link;
                                       }
                                       cout<<temp->data<<"\n";
                                       }
                                       }
                ;                 
int main()
{
stack s;
int y,n;
do
{
    cout<<"\n1.push  2.pop  3.display 4.exit\n";
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
           s.display();
           break;
           case 4:
                break;
    }
}while(y!=3);
system("pause");
return 0;
}
