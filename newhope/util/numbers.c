#include "numbers.h"

#include <math.h>

int imin(int a, int b)
{
	return a < b ? a : b;
}


int imax(int a, int b)
{
	return a > b ? a : b;
}


int sgn(int a)
{
	if(a > 0)
		return 1;
	else if(a < 0)
		return -1;
	return 0;
}
