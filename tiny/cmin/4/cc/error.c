#include "error.h"

#include <stdio.h>

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
	fprintf(stderr, "%s\n", message);
}
