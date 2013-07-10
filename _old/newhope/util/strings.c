#include "strings.h"

#include <assert.h>
#include <string.h>

int endswith(char* s, char* prefix)
{
	int pos = strlen(s) - strlen(prefix);
	assert(pos > 0);
	return strcmp(&s[pos], prefix) == 0;
}
