#include<iostream.h>
#include<string.h>
class Shortest
{
	private:
		struct Node
		{
			char vertex[5];
			int length;
			Node *next;
			Node()
			{
				vertex[0]='\0',
				length=0,
				next=NULL;
			}
		};
		struct tablenode
		{
			char vertex[5];
			int known;
			int dist;
			char path[5];
			tablenode()
			{
				vertex[0]='\0';
				known=0;
				dist=10000;
				path[0]='\0';
			}
		};
		int i;
		Node *a[100];
		tablenode b[100];
	public:
		Shortest()
		{
			cout<<"\nEnter the no.of vertices:";
			cin>>i;
			//Node *a[i];
			for(int j=0;j<i;j++)
			{
				a[j]=new Node();
				b[j].vertex[0]='\0';
				b[j].known=0;
				b[j].dist=10000;
				b[j].path[0]='\0';
			}
		}
		void takeinput()
		{
			char v[5];
			int d;
			for(int j=0;j<i;j++)
			{
				Node *t=a[j];
				cout<<"Enter the name of the "<<j+1<<" vertex: ";
				cin>>v;
				for(int t=0;t<5;t++)
				{
					a[j]->vertex[t]=v[t];
					b[j].vertex[t]=v[t];
				}
				int ch;
				cout<<"1-add adjascent vertex,0-end\n";
				cin>>ch;
				while(ch)
				{
					cout<<"Enter the adj vertex:";
					cin>>v;
					cout<<"Enter the distance:";
					cin>>d;
					Node *n=new Node();
					for(int y=0;y<5;y++)
						n->vertex[y]=v[y];
					n->length=d;
					t->next=n;
					t=n;
					cout<<"1-add,0-end:";
					cin>>ch;
				}
			}
		}
		void print()
		{
			int p;
			for(p=0;p<i;p++)
			{
				cout<<"\nVERTEX "<<p+1<<" and adj vertices:";
				Node *t=a[p];
				while(t!=NULL)
				{
					cout<<t->vertex<<"  "<<t->length<<"  \t";
					t=t->next;
				}
			}
		}
		void printtable()
		{
			cout<<"\nTABLE is:";
			for(int p=0;p<i;p++)
			{
				cout<<"\n"<<b[p].vertex<<"  "<<b[p].known<<"  "<<b[p].dist<<"  "<<b[p].path<<"  ";
			}
		}
		int check()
		{
			for(int l=0;l<i;l++)
				if(b[l].known==0)
					return 1;
			return 0;
		}
		int getindex()
		{
			int min=1001,no;
			for(int p=0;p<i;p++)
			{
				if(b[p].known==0)
				{
					if(b[p].dist<min)
					{
						min=b[p].dist;
						no=p;
					}
				}
			}
			return no;
		}
		int get(char ch[])
		{
			for(int k=0;k<i;k++)
			{
				if(strcmp(b[k].vertex,ch)==0)
					return k;
			}	
		}		
		void findpath()
		{
			char v[5];
			cout<<"Enter the vertex from where u want to find shortest path:";
			cin>>v;
			for(int h=0;h<i;h++)
			{
				if(strcmp(b[h].vertex,v)==0)
				{
					//x=h;
					b[h].dist=0;
					break;
				}
			}
			while(check())
			{
				int index=getindex();
				Node *t=a[index]->next;
				while(t!=NULL)
				{
					int g=get(t->vertex);
					if(b[index].dist+t->length<b[g].dist)
					{
						b[g].dist=b[index].dist+t->length;
						strcpy(b[g].path,t->vertex);
						//for(int q=0;q<5;q++)
						//	b[g].path[q]=b[index].vertex[q];
					}
					t=t->next;
				}
				b[index].known=1;
				printtable();
			}
		}
};
int main()
{
	Shortest s;
	system("clear");
	s.takeinput();
	cout<<"\n\n";
	//s.findpath();
	//cout<<"\nList is:";
	s.print();
	s.findpath();
	return 0;
}
