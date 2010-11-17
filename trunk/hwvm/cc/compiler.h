#ifndef COMPILER_H
#define COMPILER_H

typedef enum { _GLOBAL, _FUNCTION, _LOCAL } ContextType;

typedef struct Context {
	ContextType type;
	struct Context* previous;
} Context;

void initialize();
void new_context(ContextType type, char* fct_name);
void exit_context();


#endif
