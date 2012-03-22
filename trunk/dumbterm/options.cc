#include "options.h"

#include <memory>
using namespace std;

#include "filter_inexact.h"
#include "filter_scanline.h"

Options::Options() 
	: scale(1), w(80), h(25) 
{
	filters.push_back(new FilterScanline());
	filters.push_back(new FilterInexact(20));
}


Options::~Options()
{
}
