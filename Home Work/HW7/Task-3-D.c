#include "stdio.h"


int reversion(int c)
{
   if (c==0)
   {
        return 0;
   }
   printf("%d ", c%10);
    reversion(c/10);
}

int main()
{
    int c;
    scanf("%d",&c);
    
    if (c == 0)
    {  
        printf("0\n");
    }
    else
    {
    reversion(c);
	}
    
    return 0;
}

