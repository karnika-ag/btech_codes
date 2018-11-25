#include<iostream.h>
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
		/*struct tablenode
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
		};*/
		struct Queue
		{
			char vertex[5];
			Queue *next;
			Queue()
			{
				vertex[0]='\0';
				next=NULL;
			}
		};
		struct out
		{
			char vertex[5];
			out *next;
			out()
			{
				vertex[0]='\0';
				next=NULL;
			}
		};
		out *root,*current;
		Queue *head,*Current_Pos;
		int i;
		Node *a[100];
		
	public:
		Shortest()
		{
			cout<<"\nEnter the no.of vertices:";
			cin>>i;
			//Node *a[i];
			for(int j=0;j<i;j++)
				a[j]=new Node();
			head=new Queue();
			Current_Pos=head;
			root=new out();
			root->next=NULL;
			current=root;
			current->next=NULL;
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
					//cout<<"Enter the distance:";
					//cin>>d;
					Node *n=new Node();
					for(int y=0;y<5;y++)
						n->vertex[y]=v[y];
					//n->length=d;
					t->next=n;
					t=n;
					cout<<"1-add,0-end:";
					cin>>ch;
				}
			}
		}
		int get(char ch[])
		{
			for(int k=0;k<i;k++)
			{
				if(strcmp(a[k]->vertex,ch)==0)
					return k;
			}	
		}		
		void print()
		{
			int p;
			for(p=0;p<i;p++)
			{
				cout<<"\nVERTEX "<<p+1<<" and adj vertices:";
				Node *t=b[p];
				while(t!=NULL)
				{
					cout<<t->vertex<<"   \t";
					t=t->next;
				}
			}
		}
		int check()
		{
			for(int y=0;y<i;y++)
				if(b[y]->next!=NULL)
					return 1;
			return 0;
		}
		Node *b[100];
		void copy()
		{
			for(int k=0;k<i;k++)
				b[k]=NULL;
			for(int p=0;p<i;p++)
			{
				b[p]=new Node();
				strcpy(b[p]->vertex,a[p]->vertex);
			}
			for(int j=0;j<i;j++)
			{
				//b[j]=new Node();
				Node *tt=b[j];
				Node *t=a[j]->next;
				while(t!=NULL)
				{
					Node *h=new Node();
					strcpy(h->vertex,t->vertex);
					tt->next=h;
					tt=h;
					t=t->next;
				}
			}
		}
					
		void path()
		{
			//Node *b[100];
			char initial[5];
			for(int f=0;f<i;f++)
			{
				copy();
				root=NULL;
				root=new out();
				current=root;
				root->next=NULL;
				strcpy(initial,b[f]->vertex);
				find(initial);
			}
		}
		void putpointer(char ch[])
		{
			out *t=root->next;
			while(t!=NULL)
			{
				if(strcmp(t->vertex,ch)==0)
				{
					cout<<"     ok    ";
					break;
				}
				t=t->next;
			}
			current=t;
		}
		void printout()
		{
			cout<<"\n\nOUTPUT is:";
			out *t=root->next;
			while(t!=NULL)
			{
				cout<<"  "<<t->vertex;
				t=t->next;
			}
			cout<<"\n";
		}
		void find(char initial[])
		{
			int gg=0,count=0,c;
			c=get(initial);Node *h=b[c];
			while(h->next!=NULL)
			{
				h=h->next;
				count++;
			}
			if(count%2==1)
				count=1;
			else
				count=0;
			char ch[5];
			push(initial);
			out *z=new out();
			z->next=current->next;
			current->next=z;
			current=z;
			strcpy(z->vertex,initial);
			//cout<<"\nOrder is:"<<initial<<" ";
			strcpy(ch,initial);
			int i=check();
			//print();
			cout<<"\n";
			while(check())
			{
				int index=get(ch);
				//cout<<"8";
				fflush(stdout);
				if(b[index]->next!=NULL)
				{
					push(b[index]->next->vertex);
					strcpy(ch,b[index]->next->vertex);
					//cout<<"  "<<ch;
					out *z=new out();
					z->next=NULL;
					z->next=current->next;
					current->next=z;
					current=z;
					strcpy(z->vertex,ch);
					int p=get(ch);
					delrev(p,b[index]->vertex);
					b[index]->next=b[index]->next->next;
				}
				else
				{
					//print();
					//cout<<"\n\t   "<<initial<<"\n\t  "<<ch<<"\n";
					if(strcmp(initial,ch)!=0)
					{
						cout<<"out";
						return;
					}
					if(head->next!=NULL)
						top(ch);
					else
						return;
					while(1)
					{
						if(checkadj(ch))
						{
							if(head->next!=NULL)
							{
								pop();
								top(ch);
								//printout();
								gg=1;
								strcpy(initial,ch);
								putpointer(ch);
							}
							else
								
								return;
						}
						else
							break;
					}
				}
				i=check();
			}
			//if(gg==0&&strcmp(initial,ch)!=0)
			//	cout<<"ok";
			if((gg==1)||(strcmp(initial,ch)!=0))
			{
				//cout<<"  gg   "<<initial<<" gg   "<<ch<<"  gg  ";
				if(strcmp(initial,ch)!=0&&count==0)
				{
					cout<<"YES";
					return;
				}
			}
			cout<<"  EXIT  ";
			printout();
			cout<<"  EXIT  ";
			exit(1);
		}
		void delrev(int n,char ch[])
		{
			Node *t=b[n];
			while(1)
			{
				if(strcmp(t->next->vertex,ch)==0)
				{
					t->next=t->next->next;
					break;
				}
				else
					t=t->next;
			}
		}
		int checkadj(char ch[])
		{
			int index=get(ch);
			if(b[index]->next!=NULL)
				return 0;
			return 1;
		}
		void top(char ch[])
		{
			strcpy(ch,head->next->vertex);
		}
		void pop()
		{
			head->next=head->next->next;
		}
		void push(char ch[])
		{
			Queue *t=new Queue();
			strcpy(t->vertex,ch);
			t->next=NULL;
			Current_Pos->next=t;
			Current_Pos=t;
		}
};
int main()
{
	Shortest s;
	system("clear");
	s.takeinput();
	cout<<"\nList is:";
	//s.print();
	s.path();
	cout<<"\nEularian path is not possible\n";
	return 0;
}
