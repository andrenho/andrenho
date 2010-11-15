#ifndef UTIL_H
#define UTIL_H

typedef enum { GLOBAL, FUNCTION, LOCAL } ContextType;

typedef struct Context {
	ContextType type;
	struct Context* previous;
} Context;

void initialize();
void new_context(
void output(char* fmt, ...);

#endif
