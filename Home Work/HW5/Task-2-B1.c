#include "stdio.h"
int main()
{

int a,b;
a=0;
b=0;
//printf("enter two numbers:");
scanf("%d %d", &a, &b);



while (a<=b)
{
    printf("%d ", a*a);
    a++;
}










    return 0;
}
