#include "options.h"

#include <memory>
using namespace std;

#include "filter_inexact.h"
#include "filter_scanline.h"
#include "filter_bright.h"

Options::Options() 
	: scale(1), w(80), h(25), border_x(20), border_y(30),
	  background_color((SDL_Color) { 30, 30, 30 }),
	  bright_color((SDL_Color) { 140, 255, 190 })
{
	filters.push_back(new FilterBright(2,0));
	if(scale == 1)
		filters.push_back(new FilterInexact(15));
	else
	{
		filters.push_back(new FilterScanline());
		filters.push_back(new FilterInexact(30));
	}
}


Options::~Options()
{
	vector<Filter*>::iterator filter;
	for(filter = options.Filters()->begin(); 
			filter < options.Filters()->end(); 
			filter++)
		delete *filter;
}
