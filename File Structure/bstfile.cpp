#include<iostream>
#include<fstream>
using namespace std;
struct bindex
{int data;
	int index;
	int lindex;
   int rindex;

};
ostream &operator<<(ostream &out,bindex f)
{
	out<<f.lindex<<" "<<f.data<<" "<<f.index<<" "<<f.rindex<<" "<<endl;
	return out;
}
//void compare(int x,int y,int z);
void compare(bindex b[],int i,int j);
int main()
{  bindex b[10],f;
	int i,a[10],n,j;
	for(i=0;i<5;i++)
		{b[i].lindex=-1;
			b[i].rindex=-1;
		}
	ifstream in;
	ofstream out;
	cout<<"enter number";
	out.open("btindex.txt");
	for(i=0;i<5;i++)
		{cin>>a[i];
			out<<a[i]<<" ";}
	out.close();
	in.open("btindex.txt");
	i=-1;
	while(!in.eof())
	{ i++;
		in>>n;
		b[i].data=n;
		b[i].index=i;
		//for(j=0;j<i;j++)
           {j=0;
            	compare(b,i,j);

	}
}
	in.close();
	out.open("btindex2.txt");
    for(i=0;i<5;i++)
    {f=b[i];
      out<<f;}
out.close();
    cin.get();
    cin.get();
	return 0;
}

void compare(bindex b[],int i,int j)
{
                if(b[i].data<b[j].data)
					{if(b[j].lindex==-1)
					{b[j].lindex=i;
						}
				else
					{compare(b,i,b[j].lindex);}
			       }
				 if(b[i].data>b[j].data)
				 	{if(b[j].rindex==-1)
					{b[j].rindex=i;
						}
				else
					{compare(b,i,b[j].rindex);}
                     }
}
