#include "debug.h"

#include <stdio.h>
#include <stdarg.h>

#include "options.h"
#include "structures.h"

inline void debug(char* fmt, ...)
{
	va_list ap;

	// check if debug is on
	if(!opt.debug) 
		return;

	// parse and print message
	va_start(ap, fmt);
	fprintf(stderr, "[Server] ");
	vfprintf(stderr, fmt, ap);
	fprintf(stderr, "\n");
	va_end(ap);
}


inline void debug_comm(Client* c, Direction dir, char* fmt, ...)
{
	va_list ap;

	// check if debug is on
	if(!opt.debug) 
		return;

	// parse and print message
	va_start(ap, fmt);
	fprintf(stderr, "[Server %c %s] ", dir == FROM ? '<' : '>',
			c->id[0] == '\0' ? "Unidentified client" : c->id);
	vfprintf(stderr, fmt, ap);
	fprintf(stderr, "\n");
	va_end(ap);
}

