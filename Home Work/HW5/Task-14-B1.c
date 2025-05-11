#include "stdio.h"
int main()
{

int num=0;
int count=0;

while (1)
{
   if (scanf("%d", &num) !=1)
   {
	   return 1;
   }
   if (num==0)
   {
	   break;
   }
count ++;
}
printf("%d", count);
}
