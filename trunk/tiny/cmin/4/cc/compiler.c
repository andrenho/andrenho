#include "compiler.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include "type.h"

struct Function {
	char* name;
	struct Type* type;
};
static struct Function* current_function = NULL;

struct Variable {
	char* name;
	struct Type type;
	struct Variable* next;
};

struct Block {
	struct Variable* variables;
	struct Block* next;
	unsigned long n;
};
static struct Block* block_stack = NULL;

static unsigned long block_number = 0;


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

	current_function = malloc(sizeof(struct Function));
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
	// push a new block to the block stack
	struct Block* block = malloc(sizeof(struct Block));
	block->variables = NULL;
	block->next = block_stack;
	block->n = block_number;
	block_stack = block;

	++block_number;
}


void block_end()
{
	// pop block from the block stack
	assert(block_stack);
	struct Block* b = block_stack;
	block_stack = block_stack->next;

	// unwind variables
	// TODO
	assert(current_function);
	printf(":__%s_%ld\n", current_function->name, b->n);
	free(b);
}


void declaration()
{
	// register variable
	//struct Variable* var = malloc(sizeof(
}


void constant(unsigned long d)
{
	printf("\tSET A, 0x%lX\n", d);
}


void _return(int has_expression)
{
	if(has_expression) // do casting
		type_cast(current_type, current_function->type);
	printf("\tGOTO __%s_end\n", current_function->name);
}
