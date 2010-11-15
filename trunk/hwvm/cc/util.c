#include "util.h"

#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>

Context* context;

void initialize()
{
	context = malloc(sizeof(Context));
	context->type = GLOBAL;
	context->previous = NULL;
}


void output(char* fmt, ...)
{
	va_list ap;
	va_start(ap, fmt);
	printf("\t");
	vprintf(fmt, ap);
	printf("\n");
}
