# include <iostream.h>
# include <conio.h>

struct node
     {
      int coef;
      int exp;
      node *link;
     } *first,*mult,*f1,*f2,*temp,*item,*t1,*t2,*point;

int main()
{
 char ch;int k;
 first=NULL;
 f1=NULL;
 f2=NULL;
 mult=NULL;

 int flag=1;
 cout<<"\tFirst polynomial "<<endl;

 do
 {
  temp=new node;
  cout<<"Enter the coefficient: ";
  cin>>temp->coef;
  cout<<"Enter the degree: ";
  cin>>temp->exp;
  temp->link=NULL;
  if(f1==NULL)
  {
   f1=temp;
   item=f1;
  }
  else
  {
  item->link=temp;
  item=temp;
  }
  cout<<"Do you wish to continue...(y/n): ";
  cin>>ch;
}
while((ch=='Y')||(ch=='y'));

cout<<"\n\n\n\tEnter the second polynomial: "<<endl;

 do
 {
  temp=new node;
  cout<<"Enter the coefficient: ";
  cin>>temp->coef;
  cout<<"Enter the degree: ";
  cin>>temp->exp;
  temp->link=NULL;
  if(f2==NULL)
  {
   f2=temp;
   item=f2;
  }
  else
  {
  item->link=temp;
  item=temp;
  }
  cout<<"Do you wish to continue:...(y/n) ";
  cin>>ch;
}
while((ch=='Y')||(ch=='y'));

cout<<"\n\n\n\tMultiplied Polynomial:-"<<endl;
t1=f1;
t2=f2;
while(t1!=NULL)
{t2=f2;
 while(t2!=NULL)
 { item=new node;
   item->coef=(t1->coef)*(t2->coef);
   item->exp=(t1->exp)+(t2->exp);
   item->link=NULL;
   if(mult==NULL)
   {
    mult=item;
    temp=mult;
   }
   else
   {flag=1;
    point=mult;
    while((point!=NULL)&&(flag==1))
    {
     if((point->exp)==(item->exp))
     {(point->coef)+=(item->coef);
      flag=0;
      delete item;
     }
     point=point->link;
    }
    if(flag==1)
    {temp->link=item;
     temp=item;
    }
   }
    t2=t2->link;
  }
 t1=t1->link;
}

item=mult;
while(item!=NULL)
{if(item!=mult) cout<<" + ";
 cout<<item->coef<<"x^"<<item->exp;
 item=item->link;
}

cout<<"\n\n\n\tAdded polynomial"<<endl;
t1=f1;
t2=f2;
while((t1!=NULL)&&(t2!=NULL))
{
 if((t1->exp)<(t2->exp))
 {
  if (first==NULL)
  {
  first=t2;
  temp=first;
  }
  else
  {
   temp->link=t2;
   temp=t2;
  }
  t2=t2->link;
 }
  if((t1->exp)>(t2->exp))
 {
  if (first==NULL)
  {
  first=t1;
  temp=first;
  }
  else
  {
   temp->link=t1;
   temp=t1;
  }
  t1=t1->link;
 }

 else
 {
  (t1->coef)=(t1->coef)+(t2->coef);
  if(t2==f2)
  f2=f2->link;
  item=t2;
  t2=t2->link;
  delete item;
  if(first==NULL)
  {first=t1;
   temp=first;
  }
  else
  {
   temp->link=t1;
   temp=t1;
  }
  t1=t1->link;
 }
}

while(t1!=NULL)
{
 temp->link=t1;
 temp=t1;
 t1=t1->link;
}

while(t2!=NULL)
{
 temp->link=t2;
 temp=t2;
 t2=t2->link;
}
item=first;
while(item!=NULL)
{if(item!=first) cout<<" + ";
 cout<<item->coef<<"x^"<<item->exp;
 item=item->link;
}
cin>>k;
return 0;
}
