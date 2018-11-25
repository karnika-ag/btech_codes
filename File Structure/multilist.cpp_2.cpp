#include<iostream>
using namespace std;
struct student
{
   char name[15];
   int sub;

 };
struct subject
{   student stu;
	subject *front;
	subject *rear;
	  subject *next;

};
void addEnd(subject *&L,student m);
student delBegin(subject *&L);
void enqueue(student m,subject &s);
student delq(subject &s);
int main()
{  int n,i,j;
  student m[5],empty,q;
  subject s[5];
  for(i=0;i<5;i++)
  {s[i].front=NULL;
    s[i].rear=NULL;}

	for(i=0;i<5;i++)
 {
  cout<<"enter name of student";
  cin>>m[i].name;

  cout<<"enter number of subjects";
   cin>>n;
   for(j=0;j<n;j++)
  {cout<<"enter subjects please";
  cin>>m[i].sub;
    switch(m[i].sub)
    {
    	case 1:enqueue(m[i],s[0]);break;
    	case 2:enqueue(m[i],s[1]);break;
    	case 3:enqueue(m[i],s[2]);break;
    	case 4:enqueue(m[i],s[3]);break;
    	case 5:enqueue(m[i],s[4]);break;
    	default:break;
    }
 }
}
for(j=0;j<5;j++)
{ cout<<endl;
  cout<<"subject"<<j+1<<"student details are"<<endl;

for(i=0;i<5;i++)
{if(s[j].front!=NULL)
 {q=delq(s[j]);
 cout<<q.name<<" ";}
}
}

return 0;
 }


void addEnd(subject *&L,student m)
{
    if(L==NULL){
        L=new subject;
        L->stu=m;
        L->next=NULL;
    }
    else{
        L->next=new subject;
        L->next->stu=m;
        L->next->next=NULL;
    }
}
student delBegin(subject *&L)
{
    student a=L->stu;
    subject *P=new subject;
    P=L;
    L=L->next;
    delete(P);
    return a;
}
void enqueue(student m,subject &s){
    addEnd(s.rear,m);
    if(s.front==NULL) s.front=s.rear;
    else s.rear=s.rear->next;
}
student delq(subject &s){
    if(s.front==NULL){
        cout<<"Underflow";
        student empty;
        return empty;
    }
    if(s.front==s.rear){
        student a=delBegin(s.front);
        s.front=NULL;
        s.rear=NULL;
        return a;
    }
    return delBegin(s.front);
}
