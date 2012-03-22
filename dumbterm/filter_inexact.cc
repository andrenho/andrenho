#include "filter_inexact.h"

#include <cstdlib>
#include <algorithm>
using namespace std;

void 
FilterInexact::Apply(Screen const& screen) const
{
	/*
	srand(0);
	SDL_Surface* sf = screen.ScreenSurface();

	for(int x=0; x<sf->w; x++)
		for(int y=0; y<sf->h; y++)
		{
			int n = (rand() % (LEVEL * 2)) - LEVEL;
			int v = P(sf, x, y);
			v = min(max(v+n, 0), 255);
			P(sf, x, y) = v;
		}
	*/
}
