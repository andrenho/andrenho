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
	struct Type* type;
	struct Variable* next;
};

struct Block {
	struct Variable* variable_stack;
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
	printf("\tPUSH FP\n");
	printf("\tSET FP, PC");

	current_function = malloc(sizeof(struct Function));
	current_function->name = strdup(name);
	current_function->type = current_type;
}


void function_end(char* name)
{
	assert(current_function);

	printf("; End of function %s\n", name);
	printf(":__%s_end\n", name);
	printf("\tPOP FP\n");

	free(current_function->name);
	free(current_function);
	current_function = NULL;

	printf("\n\n");
}


void block_init()
{
	// push a new block to the block stack
	struct Block* block = malloc(sizeof(struct Block));
	block->variable_stack = NULL;
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
	unsigned int size = 0;
	struct Variable* v = b->variable_stack;
	while(v)
	{
		size += v->type->size;
		v = v->next;
	}
	printf("\tSUB ST, 0x%X\n", size/8);
	
	// end of block
	assert(current_function);
	printf(":__%s_%ld\n", current_function->name, b->n);
	free(b);
}


void declaration(const char* name)
{
	assert(block_stack);

	// register variable
	struct Variable* var = malloc(sizeof(struct Variable));
	var->name = strdup(name);
	var->type = current_type;
	var->next = block_stack->variable_stack;

	// push into variable stack
	block_stack->variable_stack = var;

	// increment program stack
	printf("\tPUSH%d A\n", var->type->size);
}


void constant(unsigned long d)
{
	printf("\tSET A, 0x%lX\n", d);
}


void _return(int has_expression)
{
	// jump over all function blocks
	unsigned int size = 0;
	struct Block* b = block_stack;
	while(b)
	{
		struct Variable* v = b->variable_stack;
		while(v)
		{
			size += v->type->size;
			v = v->next;
		}
		b = b->next;
	}
	printf("\tSUB ST, 0x%X\n", size/8);

	if(has_expression) // do casting
		type_cast(current_type, current_function->type);
	printf("\tJMP __%s_end\n", current_function->name);
}
