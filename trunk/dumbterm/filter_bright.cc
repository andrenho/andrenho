#include "filter_bright.h"

#include <cstdlib>
#include <algorithm>
using namespace std;


void 
FilterBright::Apply(Screen const& screen, Options const& opt) const
{
	SDL_Surface* sf = screen.ScreenSurface();

	if(!bsf)
		this->InitBacksurface(screen);
}


void 
FilterBright::InitBacksurface(Screen const& screen)
{
	
}


FilterBright::~FilterBright()
{
	if(bsf)
		delete[] bsf;
}
