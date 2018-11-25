#include<stdio.h>
#include<gmp.h>
#include<string.h>
#define keyLen 10
int msgLen=12;
int main()
{
	mpz_t key[10];
        mpz_t S[256],T[256];
	mpz_t temp;
	mpz_init(temp);
	unsigned long i,j,ind,k,l,count,res;
        for(i=0;i<10;i++)
	{
      
	  mpz_init(key[i]);
          mpz_random(key[i],1);
	  
	}
        for(i=0;i<256;i++)
	{
         
          mpz_init(S[i]);
	  mpz_init(T[i]);
          mpz_set_ui(S[i],i);
	}
	j=0;
	for(i=0;i<256;i++)
	{
	  mpz_set_ui(temp,j);
          mpz_add_ui(temp,S[i],j);
	  ind = (i%keyLen);
          mpz_add(temp,temp,key[ind]);
	  mpz_mod_ui(temp,temp,256);
          gmp_printf("Temp : %Zd ",temp);
          unsigned long t= mpz_get_ui(temp);
          printf("t=%lu",t);
          mpz_swap(S[i],S[t]);
	
	}
	printf("\n\n");
        for(i=0;i<256;i++)
	{
          gmp_printf("%Zd ",S[i]);
	}
	for(i=0;i<256;i++)
	{
          mpz_set(T[i],S[i]);
	}
	printf("\n\nPSUEDO RANDOM GENERATIPON ALGORITHM\n\n");
	i=0;j=0;l=0;count=0;
        char msg[200];
	char encMsg[200];
        scanf("%s",msg);
        msgLen = strlen(msg);
        printf("\nENCRYPTED MSG: ");
	while(count<msgLen)
	{
	i=(i+1)%256;
        mpz_add_ui(temp,T[i],j);
	mpz_mod_ui(temp,temp,256);
	j= mpz_get_ui(temp);
	mpz_swap(T[i],T[j]);
        mpz_add(temp,T[i],T[j]);
        mpz_mod_ui(temp,temp,256);
        l= mpz_get_ui(temp);
        k= mpz_get_ui(T[l]);
        res = k^((int)msg[count]);
        encMsg[count]=res;
	count++;
	}
        printf("\n");
        printf("%s",encMsg);

        printf("\n\nDECRYPTED MSG: "); 
        for(i=0;i<256;i++)
	{
          mpz_set(T[i],S[i]);
	}
        i=0;j=0;l=0;count=0;
        while(count<msgLen)
	{
	i=(i+1)%256;
        mpz_add_ui(temp,T[i],j);
	mpz_mod_ui(temp,temp,256);
	j= mpz_get_ui(temp);
	mpz_swap(T[i],T[j]);
        mpz_add(temp,T[i],T[j]);
        mpz_mod_ui(temp,temp,256);
        l= mpz_get_ui(temp);
        k= mpz_get_ui(T[l]);
        res = k^((int)encMsg[count]);
        printf("%c",res);
       
	count++;
	}
        printf("\n");
	return 0;
}
