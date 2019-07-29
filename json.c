#include <jansson.h>
#include <string.h>

#include "string_util.h"
#include "json.h"
#include "date_util.h"

static json_t *get_results(const char *raw_data, json_t *root)
{
    json_t *return_array;

    if (!json_is_object(root))
    {
        json_decref(root);
        return NULL;
    }
    return_array = json_object_get(root, "results");

    return return_array;
}

void json_extract_latest(const char *raw_data, measurements_t *target)
{
    double val;
    int array_size;
    parameter_t parameter_id;
    const char *parameter_string;

    json_t *root, *results, *entry, *location, *measurements, *coordinates, *latitude,
            *longitude, *country_code, *city, *measurement_line, *parameter, *date, *json_value, *unit, *source_name;
    json_error_t error;

    root = json_loads(raw_data, 0, &error);
    if (strcmp(error.text, "\0") != 0)
    {
        json_decref(root);
        target->size = 0;
        printf("Error: %s\n", error.text);
        return;
    }
    if ((results = get_results(raw_data, root)) == NULL)
    {
        target->size = 0;
        json_decref(root);
        return;
    }
    array_size = json_array_size(results);
    init_measurements(target, array_size);
    if (target->measurements_array == NULL)
    {
        puts("Error allocating memory.");
        return;
    }
    for (int i = 0; i < array_size; i++)
    {
        entry = json_array_get(results, i);
        location = json_object_get(entry, "location");
        city = json_object_get(entry, "city");
        country_code = json_object_get(entry, "country");
        coordinates = json_object_get(entry, "coordinates");
        latitude = json_object_get(coordinates, "latitude");
        longitude = json_object_get(coordinates, "longitude");

        if (!json_is_number(latitude) || !json_is_number(longitude) || !json_is_string(location) || !json_is_string(city) || !json_is_string(country_code))
            continue;

        strcpy_s(target->measurements_array[i].location, json_string_value(location), LOCATION_MAX);
        strcpy_s(target->measurements_array[i].country_code, json_string_value(country_code), COUNTRY_CODE_MAX);
        strcpy_s(target->measurements_array[i].city, json_string_value(city), CITY_MAX);
        target->measurements_array[i].latitude = json_real_value(latitude);
        target->measurements_array[i].longitude = json_real_value(longitude);

        measurements = json_object_get(entry, "measurements");
        if (!json_is_array(measurements))
            continue;
        for (int j = 0; j < json_array_size(measurements); j++)
        {
            measurement_line = json_array_get(measurements, j);
            parameter = json_object_get(measurement_line, "parameter");
            date = json_object_get(measurement_line, "lastUpdated");
            json_value = json_object_get(measurement_line, "value");
            unit = json_object_get(measurement_line, "unit");
            val = json_number_value(json_value);

            if (val < 0 || !json_is_number(json_value) || !json_is_string(unit) || !json_is_string(date) || !json_is_string(parameter))
                continue;

            parameter_string = json_string_value(parameter);
            parameter_id = string_to_param(parameter_string);
            if (parameter_id != PARAM_INVALID)
            {
                target->measurements_array[i].substances[parameter_id].value = val;
                printf("%f\n", val);
                target->measurements_array[i].substances[parameter_id].timestamp = string_to_timestamp(json_string_value(date));
                strcpy_s(target->measurements_array[i].substances[parameter_id].unit, json_string_value(unit), UNIT_MAX);
            }
            else
                printf("Unknown parameter: %s. Ignoring.\n", parameter_string);
        }
        target->measurements_array[i].valid_data = 1;
    }

    json_decref(root);
}