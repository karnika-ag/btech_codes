#include<iostream.h>
class Node
{
	public:
		int ver;
		Node *next;
		Node();
};
Node::Node()
{
	ver=0;
	next=NULL;
}
class artpoints:public Node
{
	public:
		int nv;
		int be;
		int e;
		Node **p;
		int known[20];
		int num[20];
		int low[20];
		int parent[20];
		int count;
		void getdata();
		void find_art(int v);
		int min(int a,int b);
		void createlist(int v,int pos);
		artpoints();
};
artpoints::artpoints()
{
	cout<<"Enter the number of vertices "<<endl;
	cin>>nv;
	for(int i=1;i<=nv;i++)
	{
		known[i]=0;
		num[i]=0;
		low[i]=0;
		parent[i]=0;
	}
	e=0;
	count=0;
	be=0;
}
void artpoints::getdata()
{
	int v;
	p=new Node*[nv+1];
	for(int i=0;i<nv;i++)
	{
		p[i+1]=NULL;
		char choice;
		cout<<"Enter (y/n) if there r adjacent vertices to v"<<(i+1)<<endl;
		cin>>choice;
		while(choice!='n')
		{
			cout<<"Enter the vertex adjacent to v"<<(i+1)<<endl;
			cin>>v;
			createlist(v,i+1);
			cout<<"Enter (y/n) if there r more :"<<endl;
			cin>>choice;
		}
	}
}
void artpoints::createlist(int v,int pos)
{
	e++;
	Node *current_pos=p[pos];
	Node *temp=new Node;
	temp->ver=v;
	if(p[pos])
	{
		while(current_pos->next!=NULL)
			current_pos=current_pos->next;
		current_pos->next=temp;
	}
	else
		p[pos]=temp;
}
void artpoints::find_art(int v)
{

	int j=0;
	be++;
	known[v]=1;
	low[v]=num[v]=count++;
	Node *temp=p[v];
	while(temp!=NULL)
	{
		if(known[temp->ver]==0)
		{
			parent[temp->ver]=v;
			find_art(temp->ver);
			if(low[temp->ver]>=num[v])
			{
				if(v!=1)
					cout<<"Vertex V"<<v<<"is an articulation point "<<endl;
				else
				{
					for(int i=2;i<=nv;i++)
						if(parent[i]==1)
							j++;
				}
				if(j>=2)
					cout<<"Vertex V1 is an articulation point"<<endl;
			}
			low[v]=min(low[v],low[temp->ver]);
		}
		else if(parent[v]!=temp->ver)
				low[v]=min(low[v],num[temp->ver]);
		temp=temp->next;
	}
	cout<<be<<"   ";
}
int artpoints::min(int a,int b)
{
	if(a<b)
		return a;
	else
		return b;
}
int main()
{
	//int v;
	artpoints a;
	a.getdata();
	//cout<<"Enter the source vertex "<<endl;
	//cin>>v;
	a.find_art(1);
	return 0;
}



