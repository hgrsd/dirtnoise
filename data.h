#ifndef _DATA_H_
#define _DATA_H_

#include <stdlib.h>
#include <stddef.h>
#include <time.h>

#define LOCATION_MAX 128
#define CITY_MAX 128
#define COUNTRY_MAX 64
#define COUNTRY_CODE_MAX 3
#define DATE_MAX 30
#define UNIT_MAX 12
#define N_PARAMETERS 7

// all possible parameters that may be returned
typedef enum parameter
{
    PARAM_PM25,
    PARAM_PM10,
    PARAM_O3,
    PARAM_SO2,
    PARAM_NO2,
    PARAM_CO,
    PARAM_BC,
    PARAM_INVALID
} parameter_t;

// holds raw reponses from a GET request
typedef struct _response_data_t
{
    char *data;
    int size;
} response_data_t;

typedef struct _substance_t
{
    char unit[UNIT_MAX];
    double value;
    time_t timestamp;
} substance_t;

// holds JSON-decoded measurements for a single location
typedef struct _measurement_t
{
    substance_t substances[N_PARAMETERS];
    char country_code[COUNTRY_CODE_MAX];
    char city[CITY_MAX];
    char location[LOCATION_MAX];
    int valid_data;
    double latitude;
    double longitude;
} measurement_t;

// holds a series of JSON-decoded measurements
typedef struct _measurements_t
{
    struct _measurement_t *measurements_array;
    int size;
} measurements_t;

// Clears a previously initialised and/or previously used response_data_t structure
void clear_data(response_data_t *data);

// Initialises a declared, unused response_data_t structure. Must be called before using the structure.
void init_data(response_data_t *data);
// Initialises an array of measurements. Must be called before using the structure.
void init_measurements(measurements_t *target, int nmemb);

parameter_t string_to_param(const char* string);

#endif
