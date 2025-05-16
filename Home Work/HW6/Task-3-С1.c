#include "stdio.h"
#include "math.h"


int middle(int a, int b)
{
   int result = (((b-a)/2)+a);
   
   return result;
}

int main()
{
   
int a;
int b;
scanf("%d %d",&a, &b);
int result = middle(a, b);

printf("%d", result);
   return 0;
}
 
