#include "stdio.h"
int main()
{
int a=0;
int b,b1,c,c1,d,d1,e,e1,f,f1,g,g1;

scanf("%d", &a);

b=a/1000000; //   1        0
b1=a%1000000; //  

c=b1/100000; //  2         0
c1=b1%100000; //  

d=c1/10000; //   3         0
d1=c1%10000; //  

e=d1/1000; // 4             0
e1=d1%1000;

f=e1/100; // 5              0 
f1=e1%100;

g=f1/10; // 6               0
g1=f1%10; // 7              1

//printf("%d %d %d %d %d %d %d ",b,c,d,e,f,g,g1);

if ((b==0)&&(c==0)&&(d==0)&&(e==0)&&(f==0)&&(g==0)&&(g1>0))
{
    printf("%d",g1);
}


 else if ((b==0)&&(c==0)&&(d==0)&&(e==0)&&(f==0)&&(g>0)&&(g1>=0))
 {
    printf("%d%d",g1,g);
}


else if ((b==0)&&(c==0)&&(d==0)&&(e==0)&&(f>0)&&(g>=0)&&(g1>=0))
 {
    printf("%d%d%d",g1,g,f);
}

else if ((b==0)&&(c==0)&&(d==0)&&(e>0)&&(f>=0)&&(g>=0)&&(g1>=0))
 {
    printf("%d%d%d%d",g1,g,f,e);
}

else if ((b==0)&&(c==0)&&(d>0)&&(e>=0)&&(f>=0)&&(g>=0)&&(g1>=0))
 {
    printf("%d%d%d%d%d",g1,g,f,e,d);
}

else if ((b==0)&&(c>0)&&(d>=0)&&(e>=0)&&(f>=0)&&(g>=0)&&(g1>=0))
 {
    printf("%d%d%d%d%d%d",g1,g,f,e,d,c);
}

else if ((b>0)&&(c>=0)&&(d>=0)&&(e>=0)&&(f>=0)&&(g>=0)&&(g1>=0))
 {
    printf("%d%d%d%d%d%d%d",g1,g,f,e,d,c,b);
}

else if (a==0)
 {
    printf("%d",a);
}


    return 0;
}
