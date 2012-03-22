#include "options.h"

#include "filter_inexact.h"

Options::Options() 
	: scale(2), w(80), h(25) 
{
	filters.push_back(new FilterInexact());
}


Options::~Options()
{
}
