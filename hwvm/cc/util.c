#include "util.h"

#include <stdarg.h>
#include <stdio.h>

void output(char* fmt, ...)
{
	va_list ap;
	va_start(ap, fmt);
	printf("\t");
	vprintf(fmt, ap);
	printf("\n");
}
