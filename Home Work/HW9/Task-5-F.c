//#include "stdio.h"


int find_max_array(int size, int a[])
{
int max = a[0];

for (int i = 1; i < size; i++)
{
    if(a[i]>max)
    {
        max = a[i];
    }
}
return max;
}







/*int main()
{
int a[] = {324,2342,23234,233};
int size = sizeof(a) / sizeof(a[0]);
int max = find_max_array(a, size);
printf("%d", max);
return 0;
}*/
