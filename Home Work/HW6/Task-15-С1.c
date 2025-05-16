#include "stdio.h"
#include "string.h"
#include "ctype.h"

int main()
{

char number[100]; // Буфер для хранения ввода данных

scanf("%99s",number); // Читает строку не более 99 символов


// Проверяему что цифры идут по возрастанию
int inc = 1; 

for (int i = 0; i < strlen(number) - 1; i++)
{
    if (number[i]>=number[i+1])
    {
        inc=0;
        break;
    }
}

if (inc)
{
    printf("YES");
}
else
{
    printf("NO");
}

    return 0;

}
