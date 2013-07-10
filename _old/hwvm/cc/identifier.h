#ifndef IDENTIFIER_H
#define IDENTIFIER_H

#include "types.h"

void declare_var(Type type, YYSTYPE id);
void get_var(YYSTYPE *id);
void function(Type type, YYSTYPE id);
Type function_type();
void end_function();

#endif
