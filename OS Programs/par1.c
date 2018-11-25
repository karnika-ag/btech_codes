#include <sys/types.h> 
#include <unistd.h> 
#include <stdio.h> 
#include <stdlib.h> 
#include<string.h>
int main()
{ 
	pid_t pid; 
	int rv; 
	int	commpipe[2]; 
	char s1[]="Enter Command$",s[100],myarg[100];
	printf("\n%s",s1);
	scanf("%[^'\n']s",s);
	while(strcmp(s,"exit")!=0)
	{
		 
		strcpy(myarg,"./my");
		int i=0,j=4;
		while(s[i]==' '||s[i]=='\t')
		i++;
		while(s[i]!=' '&&s[i]!='\t'&&s[i]!='\n')
		myarg[j++]=s[i++];
		myarg[j]='\0';
		strcat(myarg," ");
		strcat(myarg,s);
		if(system(myarg)<0)
		printf("\n Command not found."); 
		printf("\n%s",s1);
		char ch;
		scanf("%c",&ch);
		scanf("%[^'\n']s",s);
	}
	return 0; 
}
