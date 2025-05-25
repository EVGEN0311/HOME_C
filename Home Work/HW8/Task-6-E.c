#include "stdio.h"
int main()
{

  int number[12] = {};
   
for (int i = 0; i < 12; i++)
{
  scanf("%d", &number[i]);
}

static int result = 0;

  int size = sizeof(number) / sizeof(number[0]);
  
    for (int i = 0; i < size; i++)
  {
   result = result + number[i];
  }
  
float average = (float)result / (float)size;
printf("%.2f", average);
    return 0;
}
