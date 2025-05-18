#include "stdio.h"


void print_num(int num)
{
   if (num>=10)
   {
        print_num(num/10);
   }
   printf("%d ", num%10);
    
}

int main()
{
    int num;
    scanf("%d",&num);
    
    if (num == 0)
    {  
        printf("0\n");
    }
    else
    
    print_num(num);
	
    
    return 0;
}

