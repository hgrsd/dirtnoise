#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>

#include "api_calls.h"
#include "json.h"
#include "data.h"
#include "saw.h"

int main(int argc, char *argv[])
{
    float total_filth = 0.0;
    float left_delta;
    float right_delta;
    int sleep_ms;
    if (argc != 2) {
        printf("Usage: %s <location name>\nNote: multiple-word location names should be enclosed by \"\".\n", argv[0]);
        return 1;
    }
    response_data_t response;
    init_data(&response);
    api_fetch_latest(argv[1], &response);
    measurements_t measurements = {NULL, 0};
    json_extract_latest(response.data, &measurements);
    for (parameter_t param = PARAM_PM25; param < N_PARAMETERS; param++) {
        float val = measurements.measurements_array[0].substances[param].value;
        total_filth += val != -1 ? val : 0;
    }
    printf("total_filth: %f\nms: %f\n", total_filth, total_filth / 1000);
    sleep_ms = 1000 / (total_filth * 3) * 20000;
    printf("%d\n", sleep_ms);
    srand(time(NULL));
    if (total_filth == 0) {
        left_delta = 0.0001f;
        right_delta = 0.0002f;
        while(1) {
            playNoise(left_delta, right_delta, 50);
            usleep(5000000);
        }
    } else {
        while (1) {
            left_delta = (float) (100 + (rand() % 400)) / 100000;
            right_delta = (float) (100 + (rand() % 400)) / 100000;
            playNoise(left_delta, right_delta, 50);
            usleep(sleep_ms);
        }
    }
}