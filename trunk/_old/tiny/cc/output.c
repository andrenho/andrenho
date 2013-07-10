#include "output.h"

#include <stdarg.h>
#include <stdio.h>

static char temp[4096];

int output(char* fmt, ...)
{
	commit();

	va_list ap;
	va_start(ap, fmt);
	int n = vsnprintf(temp, 4096, fmt, ap);
	va_end(ap);

	return n;
}


void commit()
{
	if(temp[0])
		printf("%s\n", (char*)temp);
}


void rollback()
{
	temp[0] = 0;
}
