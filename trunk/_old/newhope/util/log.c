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


#if __MINGW32__
#include <stdlib.h>

void warnx(char* fmt, ...)
{
	va_list ap;
	va_start(ap, fmt);
	printf("newhope: ");
	vprintf(fmt, ap);
	printf("\n");
	va_end(ap);
}


void errx(int errcode, char* fmt, ...)
{
	va_list ap;
	va_start(ap, fmt);
	printf("newhope: ");
	vprintf(fmt, ap);
	printf("\n");
	va_end(ap);
	exit(errcode);
}

void err(int errcode, char* fmt, ...)
{
	va_list ap;
	va_start(ap, fmt);
	printf("newhope: ");
	vprintf(fmt, ap);
	printf("\n");
	perror("");
	va_end(ap);
	exit(errcode);
}

#endif

