//#include "stdio.h"
//#include "string.h"


void sort_array(int size, int arr[])
{
    for (int a = 0; a < size-1; a++)
    {
        for(int b = 0; b < size-1-a; b++)
        {
            if(arr[b] > arr[b+1])
            {
                int temper = arr[b];
                arr[b] = arr[b+1];
                arr[b+1] = temper;
            }
        }
    }
}


/*int main()
{

int a[] = {2,1,5,3,4};
int count = sizeof(a) / sizeof(a[0]);
sort_array(count, a);

    printf("");
    for(int i = 0; i < count; i++) {
        printf("%d ", a[i]);
    }
    printf("\n");




    return 0;
}*/
