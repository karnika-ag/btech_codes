#include <iostream>
#include <fstream>
using namespace std;
void sort(int arr[],int flag)
{

    int i,temp,j;
    for(i=1;i<3;i++)
    {
        temp=arr[i];
        for(j=i-1;j>=0&&arr[j]>temp;j--)
        {
            arr[j+1]=arr[j];
        }
        arr[j+1]=temp;
    }

    if(flag==1)
    {
        ofstream fout1;
        fout1.open("a1.txt",ios::app);
        fout1<<'-1'<<" ";
        for(i=0;i<3;i++)
        {
            fout1<<arr[i]<<" ";
        }
        fout1<<'-1'<<" ";
        fout1.close();
    }

    if(flag==2)
    {
        ofstream fout2;
        fout2.open("a2.txt",ios::app);
        fout2<<'-1'<<" ";
        for(i=0;i<3;i++)
        {
            fout2<<arr[i]<<" ";
        }
        fout2<<'-1'<<" ";
        fout2.close();
    }


}
int main()

{
    ifstream fin;
    ofstream fout;
    ifstream fout1;
    ifstream fout2;
    fout.open("file.txt");
    fout1.open("a1.txt");
    fout2.open("a2.txt");
    int a;
    char y='y';
    while(y=='y')
    {
        cout<<"enter the element\n";
        cin>>a;
        fout<<a<<" ";
        cout<<"want to enter more\n";
        cin>>y;
    }
    int arr[3],array[24],flag;
    int i,j,k=0;
    fin.open("file.txt");
    while(!fin.eof())
    {
        for(i=0;i<8;i++)
        {
            if(k%2==0)
            {
                flag=1;
            }
            else
            {
                flag=2;
            }
            for(j=0;j<3;j++)
            {

                fin>>(arr[i]);
              //  fin.seekg(1,ios::cur);
            }
            sort(arr,flag);
            k++;
        }

    }

    return 0;
}
