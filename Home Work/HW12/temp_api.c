#include "temp_api.h"
#include <stdio.h>
#include <limits.h>

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

float get_monthly_avg(unsigned short year, unsigned char month) 
{
    int sum = 0, count = 0;
    for (int i = 0; i < num_records; i++) {
        if (temp_data[i].year == year && temp_data[i].month == month) {
            sum += temp_data[i].temperature;
            count++;
        }
    }
    return count > 0 ? (float)sum / count : 0.0f;
    
}


char get_monthly_min(unsigned short year, unsigned char month) {
    char min_temp = CHAR_MAX; 
    int found = 0;       
    
    for (int i = 0; i < num_records; i++) {
        if (temp_data[i].year == year && temp_data[i].month == month) {
            if (!found || temp_data[i].temperature < min_temp) {
                min_temp = temp_data[i].temperature;
                found = 1;
            }
        }
    }
    if (!found)
    return CHAR_MIN;
    return min_temp;
}

   
    



char get_monthly_max(unsigned short year, unsigned char month) {
    char max_temp = -128; 
    int found = 0;      
    
    for (int i = 0; i < num_records; i++) {
        if (temp_data[i].year == year && temp_data[i].month == month) {
            if (!found || temp_data[i].temperature > max_temp) {
                max_temp = temp_data[i].temperature;
                found = 1;
            }
        }
    }
    
    return found ? max_temp : -128; 
}

float get_yearly_avg(unsigned short year) {
    int sum = 0;
    int count = 0;
    
    for (int i = 0; i < num_records; i++) {
        if (temp_data[i].year == year) {
            sum += temp_data[i].temperature;
            count++;
        }
    }
    
    return count > 0 ? (float)sum / count : 0.0f;
}

char get_yearly_min(unsigned short year) {
    char min = 127; 
    for (int i = 0; i < num_records; i++) {
        if (temp_data[i].year == year && temp_data[i].temperature < min) {
            min = temp_data[i].temperature;
        }
    }
    return min == 127 ? 0 : min; 
    
}

char get_yearly_max(unsigned short year) {
    char max = CHAR_MIN;
    int found = 0;
    
    for (int i = 0; i < num_records; i++) {
        if (temp_data[i].year == year) {
            if (temp_data[i].temperature > max) {
                max = temp_data[i].temperature;
                found = 1;
            }
        }
    }
    
    return found ? max : CHAR_MIN;
}