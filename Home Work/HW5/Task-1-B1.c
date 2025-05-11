#include "stdio.h"
int main()
{

int a,b;
//printf("enter a number:");
scanf("%d", &a);
b=1;

do
{
    printf("%d %d %d\n", b, b*b, b*b*b);
    b++;
} while (b<=a && a<100);

    return 0;
}
