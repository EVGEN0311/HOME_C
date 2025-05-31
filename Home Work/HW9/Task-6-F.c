//#include "stdio.h"

int is_two_same(int size, int a[])
{
for (int i = 0; i < size-1; i++)
{
    for (int s = i+1; s < size; s++)
    {
        if (a[i] == a[s])
        {
            return 1;
        }
        
    }
    
}
return 0;
}





/*int main()
{
int a[] = {324,2342,23234,233};
int size = sizeof(a) / sizeof(a[0]);

int max = is_two_same(size, a);
printf("%d", max);

return 0;
}*/
