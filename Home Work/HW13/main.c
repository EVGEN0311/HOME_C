#include <stdio.h>
#include "temp_api.h"
#include <string.h>
#include <stdlib.h>

void load_csv(const char* filename);

int main(int argc, char *argv[]) {

    load_csv("temperature_small.csv");
    printf("\n");
    printf("\n");
    printf("please enter: -h for the list of available commands!!! \n");
    printf("\n");
    printf("\n");
    
int size = 0;

for (int i = 1; i < argc; i++) {
        if (argv[i][0] == '-') {
            if (strcmp(argv[i], "-MinTY") == 0 && i + 1 < argc) {
                int year = atoi(argv[i + 1]);
                printf("Min temperature in %d:     %d  *C\n", year, get_yearly_min(year));
                i++; 
                }

            else if ((strcmp(argv[i], "-MinTM") == 0) && (i + 1 < argc) && (i +2 <argc)) {
                int year = atoi(argv[i + 1]);
                int month = atoi(argv[i + 2]);
                printf("Min temperature in %d %d:   %d   *C\n", year , month, get_monthly_min(year, month));
                i++;
                }
                

            else if (strcmp(argv[i], "-MaxTY") == 0 && i + 1 < argc) {
                int year = atoi(argv[i + 1]);
                printf("Max temperature in %d:     %d   *C\n", year, get_yearly_max(year));
                i++;
                }

            else if ((strcmp(argv[i], "-MaxTM") == 0) && (i + 1 < argc) && (i +2 <argc)) {
                int year = atoi(argv[i + 1]);
                int month = atoi(argv[i + 2]);
                printf("Max temperature in %d %d:   %d   *C\n", year , month, get_monthly_max(year, month));
                i++;
                }

            else if (strcmp(argv[i], "-ATY") == 0 && i + 1 < argc) {
                int year = atoi(argv[i + 1]);
                printf("Avg temperature in %d:     %.1f  *C\n", year, get_yearly_avg(year));
                i++;
                }

            else if ((strcmp(argv[i], "-ATM") == 0) && (i + 1 < argc) && (i +2 <argc)) {
                int year = atoi(argv[i + 1]);
                int month = atoi(argv[i + 2]);
                printf("Avg temperature in %d %d:   %.1f *C\n", year , month, get_monthly_avg(year, month));
                i++;
                }

            else if (strcmp(argv[i], "-h") == 0) {
                printf("-MinTY space year (Minimum temperature in current year)\n");
                printf("-MaxTY space year (Maximum temperature in current year)\n");
                printf("-ATY space year (Average temperature in current year)\n");
                printf("-MinTM space year space month number (Minimum temperature in current month)\n");
                printf("-MaxTM space year space month number (Maximum temperature in current month)\n");
                printf("-ATM space year space month number (Average temperature in current month)\n");
                i++;
                }

            else {
                printf("Unknown option: %s\n", argv[i]);
            }
        }
    }

    return 0;
}

void load_csv(const char* filename)
{
//temperature_small.csv - это файл который предстоит открыть и считать с него данные

FILE *f = fopen(filename, "r"); // открытие файла
if(f == NULL)
{
    printf("Error during reading current file!!! \n");
    return;
}



char line[256];

while (fgets(line, sizeof(line), f) != NULL)
{
    //char *f(char *f, const char *delim);
    char* token;

    token = strtok(line, ";");
    int year = atoi(token);

    token = strtok(NULL, ";");
    int month = atoi(token);

    token = strtok(NULL, ";");
    int day = atoi(token);

    token = strtok(NULL, ";");
    int hour = atoi(token);

    token = strtok(NULL, ";");
    int minute = atoi(token);

    token = strtok(NULL, ";");
    int temperature = atoi(token);

    add_record(year, month, day, hour, minute, temperature);

    
}
fclose(f); // закрытие файла
}

