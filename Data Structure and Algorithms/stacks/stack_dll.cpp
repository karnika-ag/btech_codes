#include<iostream>
using namespace std;
class stack
{
 private:
         struct node
         {
                int data;
                node *right;
                node *left;
          }*top;
public:
       stack();
       void push(int n);
       int pop();
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
                  node *p=new node;
                  p->data=n;
                  p->left=top;
                  p->right=NULL;
                  top=p;
     }
     else
     {
         node *r=new node;
         r->data=n;
         r->left=top;
         r->right=NULL;
         top->right=r;
         top=r;
     }
}
int stack::pop()
{
     if(top==NULL)
     cout<<"stack is empty\n";
     else
     {
         int m;
         node *temp;
         temp=top;
         m=temp->data;
         top=temp->right;
         delete temp;
         return m;
     }
}
void stack::display()
{
     node *q;
     q=top;
     while(q!=NULL)
     {
                          cout<<q->data<<" ";
                          q=q->left;
     }
}
int main()
{
    int n;
    char w;
    stack s;
    do
    {
        cout<<"enter the element to be pushed\n";
        cin>>n;
    
    s.push(n);
    cout<<"wanna add more...press y otherwise n\n";
    cin>>w;
    
}while(w!='n');
   
    cout<<"the elements of the stack are:\n";
    s.display();

    cout<<"\nelement deleted : "<<s.pop()<<endl;
    cout<<"the elements of the stack are:\n";
    s.display();
    system("pause");
    return 0;
}
