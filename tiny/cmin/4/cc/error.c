#include "error.h"

#include <stdio.h>
#include <stdlib.h>

extern int column;

void yyerror(char* s)
{
	fflush(stdout);
	printf("\n%*s\n%*s\n", column, "^", column, s);
}


void unsupported(char const* feature)
{
	char s[256];
	snprintf(s, 255, "%s is not yet supported.", feature);
	yyerror((char*)s);
	exit(1);
}


void warning(const char* message)
{
	fprintf(stderr, "warning: %s\n", message);
}


void _error(const char* message)
{
	char s[256];
	snprintf(s, 255, "error: %s", message);
	yyerror((char*)s);
	exit(1);
}
