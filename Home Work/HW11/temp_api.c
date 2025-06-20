#include "temp_api.h"
#include <stdio.h>

TemperatureRecord temp_data[MAX_RECORDS];
int num_records = 0;

void add_record(unsigned short year, unsigned char month, unsigned char day, unsigned char hour, unsigned char minute, char temperature) 
{
    if (num_records < MAX_RECORDS) 
    {
        temp_data[num_records].year = year;
        temp_data[num_records].month = month;
        temp_data[num_records].day = day;
        temp_data[num_records].hour = hour;
        temp_data[num_records].minute = minute;
        temp_data[num_records].temperature = temperature;
        num_records++;
    }
}

float get_monthly_avg(unsigned short year, unsigned char month) {
    return 0.0f;
}

char get_monthly_min(unsigned short year, unsigned char month) {
    return 0;
}

char get_monthly_max(unsigned short year, unsigned char month) {
    return 0;
}

float get_yearly_avg(unsigned short year) {
    return 0.0f;
}

char get_yearly_min(unsigned short year) {
    return 0;
}

char get_yearly_max(unsigned short year) {
    return 0;
}