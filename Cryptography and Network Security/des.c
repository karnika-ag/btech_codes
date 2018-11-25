#include<stdio.h>

int IP[8][8]={  {58,50,42,34,26,18,10,2},{60,52,44,36,28,20,12,4},{62,54,46,38,30,22,14,6},{64,56,48,40,32,24,16,8},
                {57,49,41,33,25,17,9,1},{59,51,43,35,27,19,11,3},{61,53,45,37,29,21,13,5},{63,55,47,39,31,23,15,7}
             };

int inverseIP[8][8];
char key[8];

int main()
{
	int i,j;
	for(i=0;i<8;i++)
	{
		  for(j=0;j<8;j++)
		  { 
			      int num = IP[i][j];
			      num-=1;
			      int res = i*8+j;
			      int r= num/8;
			      int c = num%8;
			      inverseIP[r][c] = res+1;
		  }
	}
	printf("\nInverse IP Table\n");
	for(i=0;i<8;i++)
	{
		  for(j=0;j<8;j++)
		  { 
		      printf("%d ",inverseIP[i][j]);
		  }
		  printf("\n");
	}


	printf("enter the key\n");
	scanf("%s",key);

	for(i=0;i<8;i++)
	{
		int no = key[i];
		no = no>>1;
		key[i] = no;
	}

	for(i=0;i<8;i++)
	{
		printf("(%c %d)",key[i],key[i]);
	}
	int key1 = ;
}
