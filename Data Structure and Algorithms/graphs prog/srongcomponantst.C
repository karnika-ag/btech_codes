#include<iostream.h>
class Shortest
{
	private:
		struct Node
		{
			char vertex[5];
			int length;
			Node *next;
			Node *next1;
			Node()
			{
				vertex[0]='\0',
				length=0,
				next=NULL;
			}
		};
		struct stack 
		{
			char vertex[5];
			stack *next;
			stack()
			{
				vertex[0]='\0';
				next=NULL;
			}
		};
		int i;
		Node *a[100];
		int known[100],numb[100];
		stack *head,Current_Pos;
	public:
		Shortest()
		{
			cout<<"\nEnter the no.of vertices:";
			cin>>i;
			//Node *a[i];
			for(int j=0;j<i;j++)
			{
				a[j]=new Node();
				known[j]=0;
				numb[j]=0;
			}
			head=new stack();
		}
		void takeinput()
		{
			char v[5];
			int d;
			for(int j=0;j<i;j++)
			{
				Node *t=a[j];
				cout<<"Enter the name of the "<<j+1<<" vertex";
				cin>>a[j]->vertex;
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
					cout<<t->vertex<<"  "<<t->length<<"  \t";
					t=t->next1;
				}
			}
		}
		int check()
		{
			if(head->next==NULL)
				return 0;
			return 1;
		}
		int check1()
		{
			for(int l=0;l<i;l++)
				if(known[l]==0)
					return 1;
			return 0;
		}
		int get(char ch[])
		{
			for(int k=0;k<i;k++)
			{
				if(strcmp(a[k]->vertex,ch)==0)
					return k;
			}	
		}
		void push(char ch[])
		{
			stack *t=new stack();
			for(int y=0;y<5;y++)
				t->vertex[y]=ch[y];
			t->next=head->next;
			head->next=t;
		}
		void top(char ch[])
		{
			for(int y=0;y<5;y++)
				ch[y]=head->next->vertex[y];
		}
		void pop()
		{
			head->next=head->next->next;
		}
		int findunincludedin(char ch[])
		{
			int index=get(ch);
			Node *t=a[index]->next;
			while(t!=NULL)
			{
				for(int u=0;u<5;u++)
					ch[u]=t->vertex[u];
				int i=get(ch);
				//cout<<ch<<"LL";
				if(known[i]==0)
					return 1;
				t=t->next;
			}
			return 0;
		}
		int findunincludedin1(char ch[])
		{
			int index=get(ch);
			Node *t=a[index]->next1;
			while(t!=NULL)
			{
				strcpy(ch,t->vertex);
				int h=get(ch);
				if(known[h]==0)
					return 1;
				t=t->next1;
			}
			return 0;
		}
		void dft()
		{
			int counter=1;
			char ch[5];
			int index;
			int pp=0;
			for(int kk=0;kk<i&&check1();kk++)
			{
				strcpy(ch,a[kk]->vertex);
				cout<<"initial:"<<ch<<"  ";
				head->next=NULL;
				for(int y=0;y<i;y++)
					known[y]=0;
				counter=1;
				push(ch);
				//cout<<"\norder is:"<<ch<<"  ";
				pp=get(ch);
				known[pp]=1;
				while(check())
				{
					if(head->next==NULL)
						break;
					top(ch);
					int exist=findunincludedin(ch);
					if(exist)
					{
						push(ch);
						pp=get(ch);
						known[pp]=1;
						cout<<ch<<"  ";
					}
					else
					{
						if(head->next==NULL)
							break;
						stack *mm=head->next;
						int bb=get(mm->vertex);
						numb[bb]=counter;
						//cout<<counter<<"  ";
						counter++;
						head->next=mm->next;
					}
				}
				if(!check1())
					break;
			}
		}
		void reverse()
		{
			char ch[5];
			int x;
			for(int y=0;y<i;y++)
				known[y]=0;
			for(int p=0;p<i;p++)
			{
				Node *t=a[p];
				while(t->next!=NULL)
				{
					x=get(t->next->vertex);
					insert(t->vertex,x);
					t->next=t->next->next;
				}
			}
		}
		void insert(char ch[],int x)
		{
			Node *t=new Node;
			strcpy(t->vertex,ch);
			t->next1=a[x]->next1;
			a[x]->next1=t;
		}
		int max()
		{
			int m=0,p;
			for(int h=0;h<i;h++)
				if(known[h]==0&&numb[h]>m)
				{
					m=numb[h];
					p=h;
				}
			return p;
		}
		void call()
		{
			fflush(stdout);
			while(check1())
			{
				cout<<"\nset is:  ";
				int k=max();
				find_strong(a[k]->vertex);
			}
		}		
		void find_strong(char ch[])
		{
			//char ch[5];
			int index;
			int pp=0;
			head->next=NULL;
			push(ch);
			pp=get(ch);
			known[pp]=1;
			while(check())
			{
				if(head->next==NULL)
					break;
				top(ch);
				int exist=findunincludedin1(ch);
				if(exist)
				{
					push(ch);
					pp=get(ch);
					known[pp]=1;
				}
				else
				{
					if(head->next==NULL)
						break;
					stack *mm=head;
					while(mm->next!=NULL)
					{
						cout<<mm->next->vertex<<"  ";
						mm->next=mm->next->next;
						//mm=mm->next;
					}
				}
			}
		}
		void printorder()
		{
			for(int k=0;k<i;k++)
				cout<<numb[k]<<"  ";
		}
				
};
int main()
{
	Shortest s;
	system("clear");
	s.takeinput();
	cout<<"\nList is:";
	//s.print();
	s.dft();
	s.reverse();
	s.print();
	cout<<"OUTPUT is:";
	s.call();
	fflush(stdout);
	//s.printorder();
	cout<<"\n";
	return 0;
}
