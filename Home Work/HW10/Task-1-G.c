#include "stdio.h"
#include "string.h"

int main()
{

FILE *input = fopen("input.txt", "r"); // Заранее создали файл и поместили туда "abc", теперь просто открываем его
FILE *output = fopen("output.txt", "w"); // Создаем новый файл и устанавливаем режим записи данных с самого начала удалив перед этим все что там было

if (input == NULL && output == NULL) // Делаем проверку возможности открыть файлы
{
    printf("ERROR");
    return 1;
}

char line[1000];
if (fgets(line, sizeof(line), input) == NULL)
{
    printf("ERROR");
    fclose(input);
    fclose(output);
    return 1;
}

line[strcspn(line, "\n")] = '\0';

fprintf(output, "%s, %s, %s", line, line, line);

fprintf(output, " %zu", strlen(line));

fclose(input);
fclose(output);


    return 0;
}
