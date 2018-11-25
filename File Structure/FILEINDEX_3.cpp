#include<iostream>
#include<cstdlib>
#include<cstring>
#include<fstream>
using namespace std;
class buffer
{public:
	 int n;
	 char f[40][5],g[40][5];
	 char b[100];
	 char name[20];
	 char roll[10];
	 char cgpa[5];
	 void pack();
	 void output();
	 void search();
}B;
void buffer::pack()
{ofstream fout;
 fout.open("input.txt");
 cout<<"enter no. of student:";cin>>n;
 for(int i=0;i<n;i++)
 {cout<<"name:";//cin.getline(name,19);
  cin>>name;
  f[i][1]='\0';g[i][1]='\0';
  fout<<name<<" ";
  cout<<"roll:";cin>>roll;
  fout<<roll<<" ";fout<<"$";
  cout<<"cgpa:";
  cin>>cgpa;
  //strcat(f[i],cgpa);
  strcat(g[i],cgpa);
  fout<<cgpa;//fout<<"#";
  fout<<endl;
 }
 fout.close();
}
void buffer::search()
 {char ch[5],ch1[20];int k,l=0,i=0;
   ofstream fout;ifstream fin1;
   fin1.open("input.txt");
   fout.open("index.txt");
   while(!fin1.eof())
    {fin1.getline(ch1,25,'$');
     fin1.getline(ch1,25,'\n');
     //cout<<ch1;
	 strcpy(f[i],ch1);

	 i++;
    }

   for(int i=0;i<n;i++)
    {for(int j=i;j<n;j++)
       {k=strcmp(f[i],f[j]);
         if(k==-1)
         {strcpy(ch,f[i]);
          strcpy(f[i],f[j]);
		 strcpy(f[j],ch);
         }

       }l=0;
       while(strcmp(f[i],g[l]))
       {
        l++;
       }
       fout<<l+1<<"-"<<f[i]<<endl;
		cout<<l+1<<"-"<<f[i]<<endl;
    }
    fout.close();
 }
/*void buffer::output()
 {ifstream fin3,fin2;int a,k;char ch[22];
  ofstream fout1;
  fout1.open("outputf.txt");
  fin3.open("index.txt");
  for(int i=0;i<n;i++)
  {fin3>>a;fin3.getline(ch,6,'\n');cout<<a<<" ";
    k=0;
    fin2.open("input.txt");
    for(int j=0;j<a-1;j++)
     fin2.getline(ch,22,'\n');
     fin2.getline(ch,21);
    while(ch[k]!='\0')
    { cout<<ch[k];
	  fout1<<ch[k];k++;
      if(k==10||k==16)
     { cout<<" ";fout1<<" ";
	 }
	}
	cout<<endl;fout1<<endl;
     fin2.close();
  }
 }*/
int main()
{B.pack();
 //B.unpack();
 B.search();
// B.output();
 return 0;
}
