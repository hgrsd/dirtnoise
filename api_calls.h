#ifndef _API_CALLS_H_
#define _API_CALLS_H_

#define URL_LATEST "https://api.openaq.org/v1/latest?limit=10000&%s=%s"

#define MAX_REQUEST_SIZE 256

// Fetches the latest measurements for country/city/location, stores response for further processing.
void api_fetch_latest(const char *argument, void *response);

#endif