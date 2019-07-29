#include <stdlib.h>
// copy operation was successful and buffer size was sufficient
#define COPY_SUCCESS 0
// copy operation ended prematurely due to insufficient buffer size
#define COPY_TRUNCATED 1
// invalid arguments were passed to the function
#define COPY_INVALID_ARGUMENTS 2

// Copies at most `dest_size` bytes from `src` into `dest`.
int strcpy_s(char *dest, const char *src, size_t dest_size);

// Lowercases a string in-place
void str_tolower(char *string);