#include "compiler.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include "type.h"

typedef struct {
	char* name;
	Type* type;
} Function;
Function* current_function = NULL;


void initialize()
{
	printf("; Start of code\n\n");
}

void finalize()
{
	printf("; End of code\n");
}

void function_init(char* name)
{
	printf("; Start of function: %s\n", name);
	printf(":%s\n", name);

	current_function = malloc(sizeof(Function));
	current_function->name = strdup(name);
	current_function->type = current_type;
}


void function_end(char* name)
{
	assert(current_function);

	printf("; End of function %s\n", name);
	printf(":__%s_end\n", name);

	free(current_function->name);
	free(current_function);
	current_function = NULL;

	printf("\n\n");
}


void block_init()
{
}


void block_end()
{
}


void constant(unsigned long d)
{
	printf("\tSET A, 0x%X\n", d);
}


void _return(int has_expression)
{
	if(has_expression) // do casting
		type_cast(current_type, current_function->type);
	printf("\tGOTO __%s_end\n", current_function->name);
}
