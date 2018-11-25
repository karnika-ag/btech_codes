#include<iostream>
using namespace std;
int insert(int a[],int s)
{
	if(s==31)
	{
		cout<<"OVER LOADED"<<endl;
	}
	else
	{
		int d,i;
		cout<<"Enter the DATA : ";
		cin>>d;
		a[s]=d;
		i=s;
		s=s+1;
		while(i!=1)
		{
			if(a[i]>a[i/2])
			{
				int t=a[i];
				a[i]=a[i/2];
				a[i/2]=t;
				i=i/2;
			}
			else
			{
				i=i/2;
			}
		}
	}
	return s;
}
void delete1(int a[],int s)
{
	int i,t1,t;
	if(s==1)
	{
           cout<<a[s];
   }
   else
   {
	t1=a[1];
	a[1]=a[s-1];
	a[s-1]=0;
	i=1;
	int t2,t3;
	t2=(2*i);
	t3=t2+1;
	while((a[i]<a[t2]||a[i]<a[t3])&&t2<s)
	{
		if(a[t2]>a[t3])
		{
			t=a[i];
			a[i]=a[t2];
			a[t2]=t;
			i=t2;
			t2=(2*i);
			t3=t2+1;
		}
		else
		{
			t=a[i];
			a[i]=a[t3];
			a[t3]=t;
			i=t3;
			t2=(2*i);
			t3=t2+1;
		}
	}
	cout<<t1<<"\t";
}
}
int main()
{
	int a[30],i,s;
	for(int i=0;i<30;i++)
	{
           a[i]=0;
   }
	s=1;
	int ch;
	do
	{
		cout<<"Press 1 to INSERT"<<endl;
		cout<<"Press 2 to DISPLAY SORT ORDER"<<endl;
		cout<<"Press 3 to QUIT"<<endl;
		cout<<"Enter your CHOICE : ";
		cin>>ch;
		switch(ch)
		{
			case 1:
			s=insert(a,s);
			break;
			case 2:
			while(s!=1)
			{
				delete1(a,s);
				s=s-1;
			}
			cout<<endl;
			break;
			case 3:
			break;
			default:
			cout<<"Enter correct CHOICE"<<endl;
			break;
		}
	}while(ch!=3);
	return 0;
}
