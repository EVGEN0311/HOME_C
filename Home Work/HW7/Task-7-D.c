#include "stdio.h"


int rec(int c)
{
   if (c>=1)
   {
         printf("%d ", c);
         rec(c-1);
   }
  
}

int main()
{
    int c;
    scanf("%d",&c);
    rec(c);
  
    
    return 0;
}

