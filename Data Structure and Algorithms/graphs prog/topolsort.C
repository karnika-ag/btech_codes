#include<iostream.h>
#include<string.h>
class Shortest
{
	private:
		struct Node
		{
			char vertex[5];
			Node *next;
			Node()
			{
				vertex[0]='\0',
				next=NULL;
			}
		};
		struct tablenode
		{
			char vertex[5];
			int known;
			int indegree;
			int order;
			tablenode()
			{
				vertex[0]='\0';
				indegree=0;
				known=0;
				order=0;
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
				b[j].indegree=0;
				b[j].order=0;
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
					Node *n=new Node();
					for(int y=0;y<5;y++)
						n->vertex[y]=v[y];
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
					cout<<t->vertex<<"   \t";
					t=t->next;
				}
			}
		}
		void printtable()
		{
			cout<<"\nTABLE is:";
			for(int p=0;p<i;p++)
			{
				cout<<"\n"<<b[p].vertex<<"  "<<b[p].known<<"  "<<b[p].indegree<<"  "<<b[p].order<<"  ";
			}
		}
		int check()
		{
			for(int l=0;l<i;l++)
				if(b[l].known==0)
					return 1;
			return 0;
		}
		void calindegrees()
		{
			int deg=0;
			for(int k=0;k<i;k++)
			{
				for(int l=0;l<i;l++)
				{
					Node *t=a[l]->next;
					while(t!=NULL)
					{
						if(strcmp(t->vertex,b[k].vertex)==0)
							b[k].indegree++;
						t=t->next;
					}
				}
			}
		}
		int getindex()
		{
			int min=1001,no;
			for(int p=0;p<i;p++)
			{
				if(b[p].known==0)
				{
					if(b[p].indegree==0)
						return p;
				}
			}
			cout<<"\nGraph input given is wrong,it has a loop  \n";
			exit(1);
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
			int o=1;
			/*for(int h=0;h<i;h++)
			{
				if(strcmp(b[h].vertex,v)==0)
				{
					//x=h;
					b[h].dist=0;
					break;
				}
			}*/
			int index;
			while(check())
			{
				index=getindex();
				Node *t=a[index]->next;
				while(t!=NULL)
				{
					int g=get(t->vertex);
					b[g].indegree--;
					t=t->next;
				}
				b[index].known=1;
				b[index].order=o;
				o++;
				printtable();
			}
			if(b[index].order!=i)
			{
				cout<<"\nThe input given is wrong,there is a loop in the input graph  \n";
				exit(1);
			}
			printorder();
		}
		void printorder()
		{
			cout<<"\nThe topological sorted order is:";
			int o=1;	
			while(o<=i)
			{
				for(int t=0;t<i;t++)
				{
					if(b[t].order==o)
					{
						cout<<b[t].vertex<<"  ";
						o++;
						//break;
					}
				}
			}
		}
};
int main()
{
	Shortest s;
	system("clear");
	s.takeinput();
	s.calindegrees();
	cout<<"\n\n";
	//s.findpath();
	//cout<<"\nList is:";
	s.print();
	s.printtable();
	s.findpath();
	return 0;
}
