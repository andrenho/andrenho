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


int point_in_polygon(int polySides, float* polyX, float* polyY, 
		float x, float y)
{
	int i, j=polySides-1;
	int oddNodes = 0;

	for(i=0; i<polySides; i++)
	{
		if((polyY[i] < y && polyY[j] >= y
		||  polyY[j] < y && polyY[i] >= y)
		&& (polyX[i] <= x || polyX[j] <= x))
			oddNodes ^= (polyX[i] + (y - polyY[i]) /
						(polyY[j] - polyY[i]) *
						(polyX[j] - polyX[i]) < x);
		j = i;
	}

	return oddNodes;
}
