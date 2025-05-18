#include "stdio.h"


int rec(int a, int b)
{
   if (a==b)
   {
         printf("%d ", a);
   }
   else if(a<b)
	{
	printf("%d ", a);
         rec(a+1, b);
	}
	else  
	{
		printf("%d ", a);
         rec(a-1, b);
	}
  
}

int main()
{
    int a;
    int b;
    scanf("%d %d",&a, &b);
    rec(a,b);
  
    
    return 0;
}

