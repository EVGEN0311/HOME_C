#include "stdio.h"

int main()
{

  int number[5] = {};
   
  scanf("%d %d %d %d %d", &number[0], &number[1], &number[2], &number[3], &number[4]);
    
  int min = number[0];

  int size = sizeof(number) / sizeof(number[0]);
  
    
  for (int i = 0; i < size; i++)
  {
    if (number[i] < min)
    {
        min = number[i];
    }
    
  }
  
printf("%d", min);
    return 0;
}
