#include "stdio.h"
int main()
{
	int a,b,c,d,e,m1,m2,total;
	scanf("%d%d%d%d%d",&a,&b,&c,&d,&e);
	m1=(a<b)?(a<c?a:c):(b<c?b:c);
	m2=d<e?d:e;
	total=m1<m2?m1:m2;
	printf("%d", total);
}
