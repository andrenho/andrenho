#include "util.h"

Char *StrCopyTest(Char *dst, const Char *src)
{
	if(src == NULL)
		StrCopy(dst, "");
	else
	{
		if(StrCompare(src, "") == 0)
			StrCopy(dst, "");
		else
			StrCopy(dst, src);
	}
	return dst;
}

// Routine to convert a string to a double -- Allowed input is in fixed notation ddd.fff
// This does not use MathLib.
//
double strToDouble(Char* str)
{ 
	return 0; // TODO
}
