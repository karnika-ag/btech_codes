#include<stdio.h>
//#include<conio.h>
int main()
  {
    int all[5][3]={0,1,0,2,0,0,3,0,2,2,1,1,0,0,2};
    int max[5][3]={7,5,3,3,2,2,9,0,2,2,2,2,4,3,3};
    int ava[1][3]={3,3,2};
    int need[5][3],i,j;
    int finish[5]={0};
    int k=0,s[5],l=0,fl;
   // clrscr();
    for(i=0;i<5;i++)
      {
         printf("\n Allocate:76");
        for(i=0;i<5;i++)
          {
             for(j=0;j<3;j++)
                  {
                     printf("\t%d",all[i][j]);
                  }
        printf("\n");
          }
printf("\n MAX:");
for(i=0;i<5;i++)
  {
    for(j=0;j<3;j++)
     {
        printf("\t %d",max[i][j]);
     }
printf("\n");
  }

printf("\n Available:");
for(j=0;j<3;j++)
printf("/t%d",ava[0][j]);

printf("\n\n NEED");
for(i=0;i<5;i++)
  {
    for(j=0;j<3;j++)
      {
need[i][j]=max[i][j]-all[i][j];
printf("\t%d",need[i][j]);
}
printf("\n");
}


//for(j=0;j<5;j++)
//finish[j]=0;

printf("\n");
j=0;
k=0;
l=0;
for(int x=0;x<10;x++)
  {
     if(finish[k]==1){}
     else
       {
          i=k;
          j=0;
  printf("k is %d ",k);      
  printf(" need %d %d %d  ",need[i][0],need[i][1],need[i][2]);
  printf(" ava %d %d %d  ",ava[0][0],ava[0][1],ava[0][2]);
         
         if(need[i][0]<=ava[0][0] && need[i][1]<=ava[0][1] && need[i][2]<=ava[0][2])
          fl=1; 
	  else
	   fl=0;

   printf("%d fl is %d \n",i,fl);
 printf("%d finish  & fl  is %d \n",finish[k],fl);

		if(finish[k]==0 && fl==1)
		{
printf(" hello ");
		i=k;
		for(j=0;j<3;j++)
		  {
		    ava[0][j]=ava[0][j]+all[i][j];
                    printf(" avail %d ",ava[0][j]);
		  }
		finish[k]=1;
		s[l]=k;
		l++;
		}
       }
	if(l==5)
	break;
	if(k==4)
	k=0;
	else
	k++;
}
printf("\n safe sequence is:");
for(l=0;l<5;l++)
{
printf("p%d",s[l]);
}
//getch();
}
}


