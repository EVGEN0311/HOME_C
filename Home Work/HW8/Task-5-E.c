#include "stdio.h"

int main()
{

  int number[10] = {};
   
  scanf("%d %d %d %d %d %d %d %d %d %d", &number[0], &number[1], &number[2], &number[3], &number[4], &number[5], &number[6], &number[7], &number[8], &number[9]);
  
static int result = 0;

  int size = sizeof(number) / sizeof(number[0]);
  
    
  

    for (int i = 0; i < size; i++)
  {
    if (number[i] <= 0)
   {
        result = result+0;
   }
   if (number[i] >0)
   {
    result = result + number[i];
   } 


  }
  
  
printf("%d", result);
    return 0;
}
