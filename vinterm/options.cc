#include "options.h"

#include <memory>
using namespace std;

#include "filter_inexact.h"
#include "filter_scanline.h"
#include "filter_bright.h"

Options::Options() 
	: scale(2), w(80), h(25) 
{
	//filters.push_back(new FilterBright(2,0));
	//filters.push_back(new FilterScanline());
	//filters.push_back(new FilterInexact(30));
}


Options::~Options()
{
}
