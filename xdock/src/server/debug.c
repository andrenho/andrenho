#include "debug.h"

#include <stdio.h>
#include <stdarg.h>

#include "options.h"

inline void debug(char* origin, char* fmt, ...)
{
	va_list ap;

	// check if debug is on
	if(!opt.debug) 
		return;

	// parse and print message
	va_start(ap, fmt);
	fprintf(stderr, "[%s] ", origin);
	vfprintf(stderr, fmt, ap);
	fprintf(stderr, "\n");
	va_end(ap);
}
