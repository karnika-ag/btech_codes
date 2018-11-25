#include<iostream>
using namespace std;
void insert(int a[][11])
{
	int i,j;	
	cout<<"Enter the first vertex : ";
	cin>>i;
	cout<<"Enter the second vertex : ";
	cin>>j;

	a[i][j]=1;
	a[j][i]=1;
}
int bfs(int a[][11],int i,int s,int b[],int k)
{
	if(k<11)
	{
	int t=k;
	for(int j=1;j<s+1;j++)
	{
		if(a[i][j]!=0&&i!=j)
		{
			int x=1;
			while(b[x]!=j&&b[x]!=0)
			{
				x=x+1;
			}
			if(b[x]==0)
			{
				b[k]=j;
				k=k+1;
			}
		}
	}
	while(b[t]!=0)
	{
		int y=b[t];
		k=bfs(a,y,s,b,k);
		t=t+1;
	}
	}
	return k;
}
void display(int a[][11],int s)
{
	for(int i=1;i<s+1;i++)
	{
		for(int j=1;j<s+1;j++)
		{
			cout<<a[i][j]<<"\t";
		}
		cout<<endl;
	}
}
int main()
{
	int a[11][11];
	for(int x=0;x<11;x++)
	{
		for(int y=0;y<11;y++)
		{
			a[x][y]=0;
		}
	}
	int s;
	cout<<"Enter the number of vertices : ";
	cin>>s;
	int b[11];
	for(int x=0;x<10;x++)
	{
		b[x]=0;
	}
	b[1]=1;
	int k=2;
	int ch;
	do
	{
		cout<<"Press 1 to INSERT"<<endl;
		cout<<"Press 2 to DISPLAY"<<endl;
		cout<<"Pres 3 for BFS TRAVERSAL"<<endl;
		cout<<"Press 4 to QUIT"<<endl;
		cout<<"Enter your CHOICE : ";
		cin>>ch;
		switch(ch)
		{
			case 1:
				insert(a);
				break;
			case 2:
				display(a,s);
				break;
			case 3:
				int i=1;
				k=bfs(a,i,s,b,k);
				for(int j=1;j<k;j++)
				{
					cout<<b[j]<<"\t";
				}
				cout<<endl;
				break;
		}
	}while(ch!=4);
	return 0;
}
