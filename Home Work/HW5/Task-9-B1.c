#include "stdio.h"
int main()
{
int a=0;
int b,b1,c,c1,d,d1,e1,e2,e3,e4;

scanf("%d", &a);

b=a/1000; //   2
b1=a%1000; //  222

c=b1/100; //   2
c1=b1%100; //  22

d=c1/10; //    2
d1=c1%10; //   2

e1=b%2;
e2=c%2;
e3=d%2;
e4=d1%2;




if (e1==0 && e2==0 && e3==0 && e4==0)
printf("YES");

else 
printf("NO");

    return 0;
}
