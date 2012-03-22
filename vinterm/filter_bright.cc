#include "filter_bright.h"

#include <cstdlib>
#include <algorithm>
using namespace std;


void 
FilterBright::Apply(Screen const& screen, Options const& opt) const
{
	SDL_Surface* sf = screen.ScreenSurface();
	int sp = (6-opt.scale)*2 + sharpness;

	if(!bsf)
		InitBacksurface(screen);
	for(int x=0; x<sf->w; x++)
		for(int y=0; y<sf->h; y++)
			ApplyPixel(screen, x, y, sp);

	memcpy(sf->pixels, bsf, sf->w*sf->h);
}


void 
FilterBright::ApplyPixel(Screen const& screen, int x, int y, int sp) const
{
	SDL_Surface* sf = screen.ScreenSurface();

	int c = P(sf, x, y);

	static struct { int x,y; } dirs[] = { 
		{-1,-1},{-1,0},{-1,1},
		{0,-1},{0,1},
		{1,-1},{1,0},{1,1}
	};

	// calculate light
	int total_light = 0;
	for(int i=0; i<8; i++)
	{
		int fx = x + dirs[i].x;
		int fy = y + dirs[i].y;
		if(fx < 0 || fy < 0 || fx >= sf->w || fy >= sf->h)
			continue;
		total_light += P(sf, fx, fy);
	}

	// add sharpness
	total_light += P(sf, x, y) * sp;
	c = (total_light) / (7 + sp);

	// apply brightness
	if(c > 50)
		c += (brightness * 10);
	bsf[(y*sf->w)+x] = max(min(c, 255), 0);
}


void 
FilterBright::InitBacksurface(Screen const& screen) const
{
	SDL_Surface* sf = screen.ScreenSurface();
	bsf = new uint8_t[sf->w * sf->h];
}


FilterBright::~FilterBright()
{
	if(bsf)
		delete[] bsf;
}
