#include "filter_bright.h"

#include <cstdlib>
#include <algorithm>
using namespace std;


void 
FilterBright::Apply(Screen const& screen, Options const& opt) const
{
	SDL_Surface* sf = screen.ScreenSurface();

	if(!bsf)
		InitBacksurface(screen);
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
