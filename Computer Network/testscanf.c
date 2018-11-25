#include <stdio.h>

int main (void)
{
  char str1[128], str2[128], str3[128];

  printf ("\nEnter str1: ");
  scanf ("%[^\n]%*c", str1);
  printf ("\nstr1 = %s", str1);

  printf ("\nEnter str2: ");
  scanf ("%[^\n]%*c", str2);
  printf ("\nstr2 = %s", str2);

  printf ("\nEnter str3: ");
  scanf ("%[^\n]%*c", str3);
  printf ("\nstr2 = %s", str3);

  printf ("\n");
  return 0;
}
