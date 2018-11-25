#include <iostream>
#include <fstream>
using namespace std;

struct bstind
{
    int data;
    int index;
    int lindex;
    int rindex;

};
ostream &operator<<(ostream &fout,bstind &t)
{
    fout<<t.data<<" "<<t.index<<" "<<t.lindex<<" "<<t.rindex;
    return fout;
}
void compare(bstind b[],int i,int j)
{
    if(b[i].data>b[j].data)
    {
        if(b[i].rindex==-1)
        {
            b[i].rindex=i;
        }
    }
    else
    {
        compare(b,i,b[j].rindex);
    }
    if(b[j].data>>b[i].data)
    {
        if(b[i].lindex==-1)
        {
            b[i].lindex=i;
        }

    }
    else
    {
        compare(b,j,b[j].lindex);
    }
}
int main()
{
    bstind b[5],h;
    int i,j,k,a[50];
    for(i=0;i<5;i++)
    {
        b[i].lindex=-1;
        cout<<"aaaaaaaa\n";
        b[i].rindex=-1;
    }
    ofstream fout;
    fout.open("bindex1.txt");
    for(i=0;i<5;i++)
    {
        cout<<"please type the data\n";
        cin>>a[i];
        fout<<a[i]<<endl;

    }
    fout.close();
    ifstream fin;
    fin.open("bindex1.txt");
    i=-1;
    while(!fin.eof())
    {
        i++;
        int n;
        fin>>n;
        b[i].data=n;
        b[i].index=i;
        int j=0;
        compare(b,i,j);
    }
    fin.close();
    ofstream fout1;
    fout1.open("final1.txt");
    for(i=0;i<5;i++)
    {


        fout1<<b[i]<<endl;;
    }


}
