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
    int m=-1;
    if(flag==1)
    {
        ofstream fout1;
        fout1.open("a1.txt",ios::app);
        fout1<<m<<" ";
        for(i=0;i<3;i++)
        {
            fout1<<arr[i]<<" ";
        }

        fout1.close();
    }

    if(flag==2)
    {
        ofstream fout2;
        fout2.open("a2.txt",ios::app);
        fout2<<m<<" ";
        for(i=0;i<3;i++)
        {
            fout2<<arr[i]<<" ";
        }

        fout2.close();
    }


}
void merge(int arr[],int array[],int flag)
{
    int i=0,j=0,k=0,c[6];
    while (i<3&&j<3)
    {
        if (arr[i]<array[j])
        {
            c[k++]=arr[i++];
        }
        else
        {
            c[k++]=array[j++];
        }
    }
    if (i>=3)
    {
        while(j<3)
        {
            c[k++]=array[j++];
        }
    }
    else if(j>=3)
    {
        while(j<3)
        {
            c[k++]=arr[i++];
        }
    }
    int m=-1;
    if(flag==1)
    {
        ofstream fout3;
        fout3.open("b1.txt",ios::app);
        fout3<<m<<" ";
        for(i=0;i<6;i++)
        {
            fout3<<c[i]<<" ";
        }

        fout3.close();
    }

    if(flag==2)
    {
        ofstream fout4;
        fout4.open("b2.txt",ios::app);
        fout4<<m<<" ";
        for(i=0;i<6;i++)
        {
            fout4<<c[i]<<" ";
        }


        fout4.close();
    }

}
int main()

{
    ifstream fin;
    ofstream fout;
    ifstream fout1;
    ifstream fout2;
    fout.open("file.txt");
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
    fout.close();
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
                fin>>arr[j];
                cout<<arr[j]<<" ";
            }
            sort(arr,flag);
            k++;
        }

    }
    k=0;
    ifstream fin1;
    ifstream fin2;
    fin1.open("a1.txt");
    fin2.open("a2.txt");
    int e,r,aray[3];
    for(i=0;i<4;i++)
    {
        if(k%2==0)
            {
                flag=1;
            }
            else
            {
                flag=2;
            }
        while(!fin1.eof()&&!fin2.eof())
        {
            for(j=0;j<3;j++)
            {
                fin1>>e;
                if(e!=-1)
                {
                    arr[j]=e;


                }
                /*else
                {
                    fin1.seekg(1,ios::cur);
                    fin1>>arr[j];

                }*/



                fin2>>r;
                if(r!=-1)
                {
                    aray[j]=r;

                }
                /*else
                {
                    fin2.seekg(1,ios::cur);
                    fin2>>aray[j];

                }*/
            }
            cout<<endl;
            for(int m=0;m<3;m++)
            {
                cout<<arr[m]<<" ";
            }
        }

        merge(arr,aray,flag);
        k++;

    }
    fin.close();
    fin.open("file.txt");
    int b[24],l=0;
    while(!fin.eof())
    {
        fin>>b[++l];

    }
    int h,temp,w;
    for(h=1;h<l;h++)
    {
        temp=b[h];
        for(w=h-1;w>=0&&b[w]>temp;w--)
        {
            b[w+1]=b[w];
        }
        b[w+1]=temp;
    }
    ofstream out;

    out.open("final.txt");
    for(w=0;w<l;w++)
    {
        out<<b[w]<<" ";
    }
    return 0;
}
