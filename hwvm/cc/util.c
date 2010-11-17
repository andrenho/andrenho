#include "util.h"

#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>

void print(char* fmt, ...)
{
	va_list ap;
	va_start(ap, fmt);
	vprintf(fmt, ap);
	printf("\n");
}

void output(char* fmt, ...)
{
	va_list ap;
	va_start(ap, fmt);
	printf("\t");
	vprintf(fmt, ap);
	printf("\n");
}
