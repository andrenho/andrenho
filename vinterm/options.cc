#include "options.h"

#include <memory>
using namespace std;

#include "filter_inexact.h"
#include "filter_scanline.h"
#include "filter_bright.h"

Options::Options() 
	: scale(3), w(80), h(25), border_x(20), border_y(30)
{
	filters.push_back(new FilterBright(2,0));
	filters.push_back(new FilterScanline());
	filters.push_back(new FilterInexact(30));
}


Options::~Options()
{
}
