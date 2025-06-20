#ifndef TEMP_API_H
#define TEMP_API_H

#define MAX_RECORDS 100

typedef struct {
    unsigned short year;
    unsigned char month;
    unsigned char day;
    unsigned char hour;
    unsigned char minute;
    char temperature;
} TemperatureRecord;

extern TemperatureRecord temp_data[MAX_RECORDS];
extern int num_records;

void add_record(unsigned short year, unsigned char month, unsigned char day,
                unsigned char hour, unsigned char minute, char temperature);


float get_monthly_avg(unsigned short year, unsigned char month);
char get_monthly_min(unsigned short year, unsigned char month);
char get_monthly_max(unsigned short year, unsigned char month);


float get_yearly_avg(unsigned short year);
char get_yearly_min(unsigned short year);
char get_yearly_max(unsigned short year);

#endif