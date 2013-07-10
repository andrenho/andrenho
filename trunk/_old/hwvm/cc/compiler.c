#include "compiler.h"

#include <stdlib.h>
#include <stdio.h>

#include "util.h"

Context* context;

void initialize()
{
	context = NULL;
	new_context(_GLOBAL, "global");
//	output("call main");
//	output("syscall EXIT");
}


void new_context(ContextType type, char* name)
{
	Context* c = context;
	context = malloc(sizeof(Context));
	context->type = type;
	context->name = name;
	context->variables = NULL;
	context->stack = 0;
	context->previous = c;
}


void exit_context()
{
	if(context->type == _GLOBAL)
	{
		fprintf(stderr, "Internal error: can't free global context.\n");
		abort();
	}

	Context* c = context;
	context = context->previous;
	free(c);
}
