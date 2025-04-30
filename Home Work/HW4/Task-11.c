#include "stdio.h"
int main()
{
	int a,b,c,d,e,min1,min2,totalmin,max1,max2,totalmax,sum;
	scanf("%d%d%d%d%d", &a,&b,&c,&d,&e);
	
	max1=(a>b)?(a>c?a:c):(b>c?b:c);
	max2=d>e?d:e;
	totalmax=max1>max2?max1:max2;
	
	min1=(a<b)?(a<c?a:c):(b<c?b:c);
	min2=d<e?d:e;
	totalmin=min1<min2?min1:min2;
	
	sum=totalmax+totalmin;
	
	printf("%d", sum);
	
}
