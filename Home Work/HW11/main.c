#include <stdio.h>
#include "temp_api.h"

int main() {
    
    add_record(2023, 1, 15, 12, 30, -5);
    add_record(2023, 1, 15, 18, 45, -7);
    add_record(2023, 2, 20, 9, 15, 10);
    add_record(2023, 2, 21, 15, 30, 12);
    add_record(2023, 12, 31, 23, 59, -15);

    
    printf("Average temp in 2023: %.1f\n", get_monthly_avg(2023, 1));
    printf("Min temperature in 2023: %d\n",get_yearly_min(2023));

    return 0;
}