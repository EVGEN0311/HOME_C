#include "stdio.h"
int main()
{
	int a,b,c,d,e,max1,max2,total;
	scanf("%d%d%d%d%d", &a,&b,&c,&d,&e);
	max1=(a>b)?(a>c?a:c):(b>c?b:c);
	max2=d>e?d:e;
	total=max1>max2?max1:max2;
	
	
	printf("%d", total);
	
}
