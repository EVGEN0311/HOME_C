#include <stdio.h>
#include "temp_function.h"
#include <string.h>
#include <stdlib.h>

void load_csv(const char* filename, int show_loaded);

int main(int argc, char *argv[]) {

    if (argc < 2)
    {
        printf("Usage: %s <filename.csv> [options]\n", argv[0]);
        return 1;
    }

    int show_loaded = (argc == 2);
    load_csv(argv[1], show_loaded); 
    
    
    if (show_loaded) {
        printf("\n");
        printf("please enter: -h for the list of available commands!!! \n");
        printf("\n");
        return 0; 
    }
    
    

for (int i = 2; i < argc; i++) {
        if (argv[i][0] == '-') {
            if (strcmp(argv[i], "-MinTY") == 0 && i + 1 < argc) {
                int year = atoi(argv[i + 1]);
                printf("%d\n", get_yearly_min(year));
                i++;
            } else if (strcmp(argv[i], "-MinTM") == 0 && i + 2 < argc) {
                int year = atoi(argv[i + 1]);
                int month = atoi(argv[i + 2]);
                printf("%d\n", get_monthly_min(year, month));
                i += 2;
            } else if (strcmp(argv[i], "-MaxTY") == 0 && i + 1 < argc) {
                int year = atoi(argv[i + 1]);
                printf("%d\n", get_yearly_max(year));
                i++;
            } else if (strcmp(argv[i], "-MaxTM") == 0 && i + 2 < argc) {
                int year = atoi(argv[i + 1]);
                int month = atoi(argv[i + 2]);
                printf("%d\n", get_monthly_max(year, month));
                i += 2;
            } else if (strcmp(argv[i], "-ATY") == 0 && i + 1 < argc) {
                int year = atoi(argv[i + 1]);
                printf("%.1f\n", get_yearly_avg(year));
                i++;
            } else if (strcmp(argv[i], "-ATM") == 0 && i + 2 < argc) {
                int year = atoi(argv[i + 1]);
                int month = atoi(argv[i + 2]);
                printf("%.1f\n", get_monthly_avg(year, month));
                i += 2;
            } else if (strcmp(argv[i], "-h") == 0) {
                printf("-MinTY <year>\n");
                printf("-MaxTY <year>\n");
                printf("-ATY <year>\n");
                printf("-MinTM <year> <month>\n");
                printf("-MaxTM <year> <month>\n");
                printf("-ATM <year> <month>\n");
            } else {
                printf("Unknown option: %s\n", argv[i]);
            }
        }
    }

    return 0;
}

void load_csv(const char* filename, int show_loaded)
{
    FILE *f = fopen(filename, "r");
    if (f == NULL) {
        printf("Error during reading current file!!! \n");
        return;
    }

    char line[256];
    while (fgets(line, sizeof(line), f) != NULL) {
        char* token = strtok(line, ";");
        if (token == NULL) continue;
        int year = atoi(token);

        token = strtok(NULL, ";");
        if (token == NULL) continue;
        int month = atoi(token);

        token = strtok(NULL, ";");
        if (token == NULL) continue;
        int day = atoi(token);

        token = strtok(NULL, ";");
        if (token == NULL) continue;
        int hour = atoi(token);

        token = strtok(NULL, ";");
        if (token == NULL) continue;
        int minute = atoi(token);

        token = strtok(NULL, ";");
        if (token == NULL) continue;
        int temperature = atoi(token);

        if (show_loaded) {
            printf("Loaded: %04d-%02d-%02d %02d:%02d = %d*C\n", year, month, day, hour, minute, temperature);
        }

        add_record(year, month, day, hour, minute, temperature);
    }

    fclose(f);
}

