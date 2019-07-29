#include <string.h>
#include <stdio.h>

#include "date_util.h"
#include "data.h"

time_t string_to_timestamp(const char *string)
{
    struct tm tm_from_string = {0};
    time_t timestamp_from_string;

    strptime(string, "%Y-%m-%dT%H:%M:S.", &tm_from_string);
    timestamp_from_string = mktime(&tm_from_string);

    return timestamp_from_string;
}

void timestamp_to_string(char *string, time_t timestamp)
{
    struct tm *tm_from_timestamp;
    tm_from_timestamp = gmtime(&timestamp);
    strftime(string, DATE_MAX, "%d/%m/%Y @ %H:%M", tm_from_timestamp);

    return;
}

void date_convert_to_us(const char *date, char *us_date)
{
    int day, month, year;
    sscanf(date, "%2d/%2d/%4d", &day, &month, &year);
    snprintf(us_date, DATE_MAX - 1, "%d-%d-%d", year, month, day);
}