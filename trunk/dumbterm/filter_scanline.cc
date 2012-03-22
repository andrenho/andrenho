#include "filter_scanline.h"

#include <cstdlib>
#include <algorithm>
using namespace std;

void 
FilterScanline::Apply(Screen const& screen, Options const& opt) const
{
	srand(0);
	SDL_Surface* sf = screen.ScreenSurface();

	for(int y=0; y<sf->h; y++)
		if((y / opt.scale) % each == 0)
			for(int x=0; x<sf->w; x++)
			{
				double v = P(sf, x, y) * level;
				P(sf, x, y) = (Uint8)v;
			}
}
