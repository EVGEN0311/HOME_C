// Домашнее задание А-12
#include "stdio.h"

int main()
{
	
	// Вариант-1
	/*char a[3];
	printf("enter the numbr:\n");
	scanf("%c%c%c",&a[0],&a[1], &a[2]);
	int d= (a[0]-'0')+ (a[1]-'0')+(a[2]);
	printf("%d",d);*/
	
	/*int a,b,c,e,sum;
	a=123;
	e = a;
	b=a%100/10;
	a=a/100;
	c=e-((a*100)+(b*10));
	sum=a+b+c;
	printf("%d",sum);*/
	
	int a,b,c,e,sum;
	a=0;
	scanf("%d",&a);
	e = a;
	b=a%100/10;
	a=a/100;
	c=e-((a*100)+(b*10));
	sum=a+b+c;
	printf("%d",sum);
}
