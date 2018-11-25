#include <iostream>
#include <fstream>
#include <cstdlib>
#include <cstring>
using namespace std;
struct trinode;
struct alpha
{
    char cha[26];
    trinode *ptr[27];
};
struct trinode
{
    int tag;
    union
    {
        alpha ch;
        int rno;
    };

};
void makealpha(trinode *&t)   //for tag=1
{
    if(t==NULL)
    {
        t=new trinode;
       // t->ch.cha[]={'A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z'};
        for(int i=0,j=65;i<27,j<92;i++,j++)
        {
            if(j<91)
            {
                t->ch.cha[i]=j;
            }
            t->ch.ptr[i]=NULL;
        }
        t->tag=1;
    }
}
void makerec(trinode *&t) //for tag=0
{
    if(t==NULL)
    {
        t=new trinode;
        t->tag=0;
        t->rno=0;
    }
}
void create(trinode *&t,char k,char str[],int count)
{
    if(k!='\0'&&t==NULL)
    {
        makealpha(t);
        for(int i=0;i<26;i++)
        {
            if(t->ch.cha[i]==k)
            {
                k=str[++count];
                create(t->ch.ptr[i],k,str,count);
               break;
            }
        }
    }
    else if(k=='\0'&&t==NULL)
    {
        makerec(t);
        t->rno=count++;
        cout<<"t->rno "<<t->rno<<endl;
        return;

    }
    if(k!='\0'&&t!=NULL)
    {
        for(int i=0;i<26;i++)
        {
            if(t->ch.cha[i]==k)
            {
                k=str[count++];
                create(t->ch.ptr[i],k,str,count);
                break;
            }
        }
    }
    else if(k=='\0'&&t==NULL)
    {
        makerec(t);
        t->rno=count++;

        return;

    }
/*
if(k!='\0'&&tag==0&&t!=NULL)
    {
        for(int i=0;i<26;i++)
        {
            if(t->ch.cha[i]==k)
            {
                k=str[count++];
                create(t->ch.ptr[i],k,str,count);
                break;
            }
        }
    }
    else if(k=='\0'&&t==NULL)
    {
        makerec(t);
        t->rno=count++;

        return;

    }
    */

}
int main()
{
    int i=0,j,count=0;
    char k,st[10],str[10];
    cout<<"Please enter the number of strings to be entered\n";
    cin>>i;
    trinode *t=NULL;
    //t=new trinode;
    for(j=0;j<i;j++)
    {
        cout<<"string\n";
        cin>>st;
       // cin.getline(st,10);

       // getc(stdin);            //to not let enter goto next line
        strcpy(str,st);
        k=str[0];
        cout<<k<<endl;
        for(int k=0;str[k]!='\0';k++)
        {
            cout<<str[k]<<endl;
        }
        create(t,k,str,count);

    }

}
