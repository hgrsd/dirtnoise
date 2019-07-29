#include <curl/curl.h>
#include <string.h>
#include <stdlib.h>

#include "api_calls.h"
#include "data.h"

static int write_callback(void *input, size_t size, size_t nmemb, void *target)
{
    response_data_t *received = (response_data_t *)target;
    char *ptr = realloc(received->data, received->size + nmemb + 1);

	received->data = ptr;
	memcpy(&(received->data[received->size]), input, nmemb);
	received->size += nmemb;
	received->data[received->size] = '\0';

	return nmemb;
}

static void api_init(void)
{
	static int initialised = 0;

	if (!initialised)
		curl_global_init(CURL_GLOBAL_ALL);

	initialised = 1;
}

static void fetch_data(const char *request, void *response)
{
    CURL *curl_handle;
    CURLcode curl_response;

    api_init();
    curl_handle = curl_easy_init();
    if (curl_handle)
    {
        curl_easy_setopt(curl_handle, CURLOPT_URL, request);
        curl_easy_setopt(curl_handle, CURLOPT_WRITEFUNCTION, write_callback);
        curl_easy_setopt(curl_handle, CURLOPT_WRITEDATA, response);
        curl_easy_setopt(curl_handle, CURLOPT_USERAGENT, "Mozilla Firefox");
    }
    printf("%s\n", request);
    curl_response = curl_easy_perform(curl_handle);
    if (curl_response != CURLE_OK)
        fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(curl_response));

    curl_easy_cleanup(curl_handle);
}

void api_fetch_latest(const char *argument, void *response)
{
    char request[MAX_REQUEST_SIZE];
    char *argument_urlencoded;

    CURL *curl_handle;
    curl_handle = curl_easy_init();

    argument_urlencoded = curl_easy_escape(curl_handle, argument, 0);

    snprintf(request, MAX_REQUEST_SIZE - 1, URL_LATEST, "location", argument_urlencoded);
    fetch_data(request, response);

    curl_easy_cleanup(curl_handle);
}