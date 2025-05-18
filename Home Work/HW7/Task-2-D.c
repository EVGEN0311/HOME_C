#include "stdio.h"


int rec(int c)
{
    if (c==1)
    {       
        return 1;
    }
    return c + rec(c -1);
}

int main()
{
int c=0;
scanf("%d",&c);
rec(c);

printf("%d",rec(c));
    return 0;
}
