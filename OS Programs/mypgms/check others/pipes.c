 #include<stdio.h>  
 #include<unistd.h>  
 #include<string.h>  
 void main()  
 {  
  
  int pid[2],pid1[2],pid2[2],pid3[2],pid4[2];  
  int a[20],i,l,s=0;  
  char str[20];  
  pipe(pid);  
  pipe(pid1);  
  pipe(pid2);  
  pipe(pid3);  
  pipe(pid4);   
 if(fork()==0)  
 {  
  sleep(5);  
  close(pid[1]);  
  read(pid[0],str,sizeof(str));  
  for(i=0,l=0;str[i]!='\0';i++)  
  l=l+1;  
  close(pid3[0]);  
  write(pid3[1],&l,sizeof(l));  
  sleep(6);  
  printf("Enter %d array elementz:",l);  
  for(i=0;i<l;i++)  
  scanf("%d",&a[i]);  
  close(pid1[0]);  
  write(pid1[1],a,sizeof(a));  
  close(pid4[0]);  
  write(pid4[1],&l,sizeof(l));  
 }  
 else if(fork()==0)  
 {  
  sleep(2);  
  close(pid1[1]);  
  close(pid4[1]);  
  read(pid4[0],&l,sizeof(l));  
  read(pid1[0],a,sizeof(a));  
  for(i=0;i<l;i++)  
  s=s+a[i];  
  close(pid2[0]);  
  write(pid2[1],&s,sizeof(s));  
 }   
 else    
 {  
  printf("\nEnter string:");  
  scanf("%s",str);  
  close(pid[0]);  
  write(pid[1],str,sizeof(str));  
  sleep(7);  
  close(pid3[1]);  
  read(pid3[0],&l,sizeof(l));  
  printf("\nThe string length=%d",l);  
  sleep(8);  
  close(pid2[1]);  
  read(pid2[0],&s,sizeof(s));  
  printf("\nSum=%d",s);  
 }  
 }  
