#include <iostream>
#include <fstream>
using namespace std;
struct  bstnode
{
    bstnode *lchild;
    int data;
    bstnode *rchild;
};

void createbst(bstnode *&t)
{
    char q;

    if(t==NULL)
    {
        t=new bstnode;
        t->data=-1;
        t->lchild=NULL;
        t->rchild=NULL;

         }



        cout<<"Please enter the left element of "<<t->data<<endl;
        cin>>q;
        if(q!='.')
        {
            createbst(t->lchild,q);
        }
        cout<<"Please enter the right element of "<<t->data<<endl;
        cin>>q;
        if (q!='.')
        {


        createbst(t->rchild,q);
        }
    }

