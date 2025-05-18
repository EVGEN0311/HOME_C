#include "stdio.h"


void rec(int b)
{
    
  
static int a=1;


    if (a<=b)
    {
        printf("%d ", a);
        a++;
        rec(b);
    }
    
}

int main()
{
	//int c=0;
	int b=0;
	scanf("%d",&b);
	//printf("%d ",c);
rec(b);
    return 0;
}
