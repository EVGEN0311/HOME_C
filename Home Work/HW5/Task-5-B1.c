#include "stdio.h"
int main()
{




int a=0;
scanf("%d", &a);
int b1,b2,c1,c2,d1,d2,e1,e2;

b1=a/10000; //1
b2=a%10000; // 1111

c1=b2/1000; //1
c2=b2%1000; //111

d1=c2/100; //1
d2=c2%100; //11

e1=d2/10; //1
e2=d2%10; //1

printf("%d", b1+c1+d1+e1+e2);










    return 0;
}
