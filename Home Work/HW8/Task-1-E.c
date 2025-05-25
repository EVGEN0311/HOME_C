#include "stdio.h"

int main()
{

    int number[5];
    int size = sizeof(number) / sizeof(number[0]);
    int sum = 0;

    scanf("%d %d %d %d %d", &number[0], &number[1], &number[2], &number[3], &number[4]);
    
    //int size_number = sizeof(number);
    //printf("size_number = %d \n", size_number);

    //int size_number2 = sizeof(number[0]);
    //printf("size_number2 = %d \n", size_number2);

    for (int i=0; i<size; i++)
    {
        sum+=number[i]; // sum=sum+number[1];
    }

    float average = (float)sum/(float)size;
//printf("sum = %d \n", sum);
printf("%.1f", average);

    return 0;
}
