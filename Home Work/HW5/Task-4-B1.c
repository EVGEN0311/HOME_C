#include "stdio.h"
int main()
{
int a;
//printf("enter the number:");
scanf("%d", &a);

if (a<100 || a>999)
{
    printf("NO");
}

else if (a>=100 || a<1000)
{
   printf("YES");
}

}
