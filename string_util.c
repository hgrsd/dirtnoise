#include <ctype.h>
#include <string.h>

#include "string_util.h"


int strcpy_s(char *dest, const char *src, size_t dest_size)
{
	if(dest_size < 1 || !dest)
	{
		return COPY_INVALID_ARGUMENTS;
	}

	if(dest_size == 1)
	{
		*dest = '\0';
		return COPY_TRUNCATED;
	}

	for(char *end = dest + dest_size - 1;
		(dest != end || (*dest = '\0')) && (*dest = *src);
		dest++, src++);
		
	return 0;
}

void str_tolower(char *string)
{
	for (int i = 0; i < strlen(string); i++)
	{
		string[i] = tolower(string[i]);
	}
}