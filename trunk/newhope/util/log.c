#include "log.h"

#include <stdio.h>
#include <stdarg.h>

static int show_debug = 0;

void log_init(int sdebug)
{
	show_debug = sdebug;
}


void debug(char* fmt, ...)
{
	if(!show_debug)
		return;

	va_list ap;
	va_start(ap, fmt);
	printf("newhope: debug: ");
	vprintf(fmt, ap);
	printf("\n");
	va_end(ap);
}
