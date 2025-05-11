#include "stdio.h"
int main()
{
int a=0;
int b,b1,c,c1,d,d1;

scanf("%d", &a);

b=a/1000; //   2
b1=a%1000; //  222

c=b1/100; //   2
c1=b1%100; //  22

d=c1/10; //    2
d1=c1%10; //   2




printf("%d%d%d%d", d1,d,c,b);

    return 0;
}
