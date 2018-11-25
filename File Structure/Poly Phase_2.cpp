#include<iostream>
#include<fstream>
#include<cstdlib>
#include<cstring>
using namespace std;
int getMinIndex(int* st,int size)
{
    int minIndex=0,min=9999;
    for(int i=0;i<size;i++)
    {
        if(st[i]<min && st[i]!=-1)
        {
            min=st[i];
            minIndex=i;
        }
    }
    return minIndex;
}
int fileSort(char* F1, int f1, char* F2, int f2, char* F3, int f3, char* F4)
{
    ifstream fin[3];
    ofstream fout;
    if(f1==-2)
    {
        fout.open(F1);
        fout<<-1;
        fout.close();
        f1=0;
    }
    if(f2==-2)
    {
        fout.open(F2);
        fout<<-1;
        fout.close();
        f2=0;
    }
    if(f3==-2)
    {
        fout.open(F3);
        fout<<-1;
        fout.close();
        f3=0;
    }
    fin[0].open(F1);
    fin[0].seekg(f1,ios::beg);
    fin[1].open(F2);
    fin[1].seekg(f2,ios::beg);
    fin[2].open(F3);
    fin[2].seekg(f3,ios::beg);
    int count[3]={0,0,0};
    int data[3];
    for(int j=0;j<3;j++)
        while(!fin[j].eof())
        {
            fin[j]>>data[j];
            if(data[j]==-1)
                count[j]++;
        }
    for(int i=0;i<3;i++)
        fin[i].close();
    int minIdx=getMinIndex(count,3);
    if(count[minIdx]==0)
    {
        cout<<"\nProgram Executed Successfully\n";
        return (1);
    }
    fin[0].open(F1);
    fin[0].seekg(f1,ios::beg);
    fin[1].open(F2);
    fin[1].seekg(f2,ios::beg);
    fin[2].open(F3);
    fin[2].seekg(f3,ios::beg);
    fout.open(F4);
    int st[3];
    for(int i=0;i<3;i++)
        fin[i]>>st[i];
    int x=getMinIndex(st,3);
    int change=0;
    char ch;
    while(change < count[minIdx]-1)
    {
        if(st[x]!=-1)                           //bcz x always has smaller value its element will be put into file.........which can't be zero
        {
            fout<<st[x]<<" ";    //each time an element is entered into file count++
            fin[x].get(ch);
            if(!fin[x].eof())
                fin[x]>>st[x];
            else
                st[x]=-1;
            x=getMinIndex(st,3);
        }
        else                                    //if st[x]==-1 that means one partition is completely poured into file
        {
            fout<<-1<<" ";                     //putting -1 after every partition
            change++;
            for(int i=0;i<3;i++)
            fin[i]>>st[i];
            x=getMinIndex(st,3);
        }
    }
    fout.close();
    if(minIdx==0)
    {
        f2=fin[1].tellg();
        f3=fin[2].tellg();
        return fileSort(F2,f2-1,F3,f3-1,F4,0,F1);
    }
    else if(minIdx==1)
    {
        f1=fin[0].tellg();
        f3=fin[2].tellg();
        return fileSort(F1,f1-1,F3,f3-1,F4,0,F2);
    }
    else if(minIdx==2)
    {
        f1=fin[0].tellg();
        f2=fin[1].tellg();
        return fileSort(F2,f2-1,F1,f1-1,F4,0,F3);
    }
}
int main()
{
    int a;
    fileSort("file1.txt",0,"file2.txt",0,"file3.txt\0",0,"file4.txt");
    ifstream fin("file1.txt");
    cout<<"\nSorted Numbers:\n";
    while(!fin.eof())
    {
        fin>>a;
        if(a!=-1)
        cout<<a<<" ";
    }
}
