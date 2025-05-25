#include "stdio.h"

int main()
{

  int number[10] = {};
   
  scanf("%d %d %d %d %d %d %d %d %d %d", &number[0], &number[1], &number[2], &number[3], &number[4], &number[5], &number[6], &number[7], &number[8], &number[9]);
    
  int min = number[0];
  int max = number[0];

  int size = sizeof(number) / sizeof(number[0]);
  //printf("%d", size);
    
  for (int i = 0; i < size; i++)
  {
    if (number[i] < min)
    {
        min = number[i];
    }
    
  }

  for (int i = 0; i < size; i++)
  {
    if (number[i] > max)
    {
        max = number[i];
    }
    
  }
  
  int sum = max + min;
printf("%d", sum);
    return 0;
}
