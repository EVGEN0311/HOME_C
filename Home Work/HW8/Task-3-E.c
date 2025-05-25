#include "stdio.h"

int main()
{

  int numbers[10];

  for (int i = 0; i < 10; i++)
  {
    scanf("%d", &numbers[i]);
  }
  
  int min = numbers[0];
  int max = numbers[0];
  int min_index = 0;
  int max_index = 0;

  for (int i = 0; i < 10; i++)
  {
    if (numbers[i] < min)
    {
      min = numbers[i];
      min_index = i+1;
    }
    
    if (numbers[i] > max)
    {
      max = numbers[i];
      max_index = i+1;
    }
    

  }
  
printf("%d %d %d %d", max_index, max, min_index, min);
  

    return 0;
}
