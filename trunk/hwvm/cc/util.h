#ifndef UTIL_H
#define UTIL_H

struct YYSTYPE {
	char* value;
	int type;
};
#define YYSTYPE struct YYSTYPE

typedef enum { GLOBAL, FUNCTION, LOCAL } ContextType;

typedef struct Context {
	ContextType type;
	struct Context* previous;
} Context;

void initialize();
void new_context(ContextType type, char* fct_name);
void exit_context();
void print(char* fmt, ...);
void output(char* fmt, ...);
void gettype(YYSTYPE type);
YYSTYPE cast(YYSTYPE val1, YYSTYPE val2);

#endif
