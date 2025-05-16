#include "stdio.h"
#include "math.h"


int povi(int a, int b)
{
   int result = (int)round(pow(a,b));
   
   return result;
}

int main()
{
   
int a;
int b;
scanf("%d %d",&a, &b);
int result = (int)povi(a, b);

printf("%d", result);
   return 0;
}
 
