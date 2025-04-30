#include "stdio.h"
int main()
{
	int a,a1,a2,a3,max;
	scanf("%d",&a);
	
	a1=a/100;
	a2=(a-(a1*100))/10;
	a3=a-(a1*100)-(a2*10);
	
	max=(a1>a2)?(a1>a3?a1:a3):(a2>a3?a2:a3);
	printf("%d",max);
}
