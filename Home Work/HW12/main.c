#include <stdio.h>
#include "temp_api.h"
#include <string.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    
    add_record(2023, 1, 15, 12, 30, -5);
    add_record(2023, 1, 15, 18, 45, -7);
    add_record(2023, 2, 20, 9, 15, 19);
    add_record(2023, 2, 21, 15, 30, 12);
    add_record(2023, 12, 31, 23, 59, -15);

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
                int year = atoi(argv[i + 1]);
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
