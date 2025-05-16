#include <stdio.h>
 

int sum (int x)
{
    int sum = x*(x+1)/2;
    return sum;
}



int main(void)
{

    int x;
   scanf("%d",&x);
   int result = sum(x);
    printf("%d",result);
 
    return 0;
}
