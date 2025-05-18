#include "stdio.h"

int sum_digits(int n)



{
	
	if(n<10)
	{
		return n;
	}
	else if (n>=10)
	{
		return n%10 + sum_digits(n/10);
		
	}
}



int main()
{
	
	int n=0;
    scanf("%d", &n);
    printf( "%d", sum_digits(n) );
	
	return 0;
}
