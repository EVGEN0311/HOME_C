// Домашнее задание А-13
#include "stdio.h"

int main()
{
	
	int a,b,c,e,sum;
	a=0;
	scanf("%d",&a);
	e = a;
	b=a%100/10;
	a=a/100;
	c=e-((a*100)+(b*10));
	sum=a*b*c;
	printf("%d",sum);
}
