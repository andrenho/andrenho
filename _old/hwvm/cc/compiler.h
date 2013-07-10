#ifndef COMPILER_H
#define COMPILER_H

#include "types.h"

typedef enum { _GLOBAL, _FUNCTION, _LOCAL } ContextType;

typedef struct Variable {
	char* name;
	char* id;
	Type type;
	struct Variable* next;
} Variable;

typedef struct Context {
	ContextType type;
	char* name;
	Variable* variables;
	int stack;
	struct Context* previous;
} Context;

extern Context* context;

void initialize();
void new_context(ContextType type, char* fct_name);
void exit_context();


#endif
