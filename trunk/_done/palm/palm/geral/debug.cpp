#include "debug.h"
#include "palmincludes.h"

void debug(char* s)
{
	ErrDisplay(s);
}

void debug(int i)
{
	char b[20];
	sprintf(b, ">> %d <<", i);
	ErrDisplay(b);
}
