 #include<iostream>
#include<fstream>
using namespace std;
struct btnode
 {
 int data;
 btnode *right;
 btnode *left;
 }*s;
typedef btnode* bt;

void insert(bt &T,int n)
{
    if(T==NULL)
    {
    T=new btnode;
    T->data=n;
    T->right=NULL;
    T->left=NULL;
    }
    else
    {
        if(n>T->data)
        insert(T->right,n);
        else
        {
            if(n<T->data)
            insert(T->left,n);
            else
            cout<<"wrong input\n";
        }
    }
}
void search(bt &T,int n)
{
    int c;
    c=0;
    if(T!=NULL)
    {
     if (n==T->data)
     c=1;
     else if(n>T->data)
     {
     search(T->right,n);
     c=2;
     }
     else
     {
     search(T->left,n);
     c=2;
     }
    }
    if(c==1)
    cout<<"\nelement found\n";
    if(c==0)
    cout<<"\nelement not found\n";
    }

int main()
{
  btnode *s=NULL;
  int a;
  do
  {
  cout<<"press 1 to enter the element...\n2 to search an element..\n3 to terminate the program..\n";
  cout<<"enter ur choice\n";
  cin>>a;
  switch(a)
  {
           case 1:
                int n;
                cout<<"enter the value to be inserted\n";
                cin>>n;
                insert(s,n);
                break;
           case 2:
                 int y;
                 cout<<"enter the value to be searched\n";
                 cin>>y;
                 search(s,y);
                 break;
           case 3:
                break;
  }
  }while(a!=3);
  system("pause");
  return 0;
}
