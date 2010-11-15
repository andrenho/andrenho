#ifndef UTIL_H
#define UTIL_H

typedef enum { GLOBAL, FUNCTION, LOCAL } ContextType;

typedef struct Context {
	ContextType type;
	struct Context* previous;
} Context;

void initialize();
void new_context(ContextType type);
void exit_context();
void print(char* fmt, ...);
void output(char* fmt, ...);

#endif
