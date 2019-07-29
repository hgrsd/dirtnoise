#ifndef _JSON_H_
#define _JSON_H_

#include "data.h"

// Extracts measurements from the raw string and stores them as an array of measurement_t structs.
void json_extract_latest(const char *raw_data, measurements_t *target);

void json_extract_measurements(const char *raw_data, measurements_t *target);

#endif
