#include "util.h"

#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>

Context* context;

void initialize()
{
	context = NULL;
	new_context(GLOBAL, NULL);
	output("call main");
	output("syscall EXIT");
}


void new_context(ContextType type, char* fct_name)
{
	(void) fct_name;

	Context* c = context;
	context = malloc(sizeof(Context));
	context->type = type;
	context->previous = c;
}


void exit_context()
{
	if(context->type == GLOBAL)
	{
		fprintf(stderr, "Internal error: can't free global context.\n");
		abort();
	}

	Context* c = context;
	context = context->previous;
	free(c);
}

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

