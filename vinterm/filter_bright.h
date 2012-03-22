#ifndef FILTER_BRIGHT_H
#define FILTER_BRIGHT_H

#include <cstdio>
#include "filter.h"

class FilterBright : public Filter
{
public:
	FilterBright(double level=1) 
		: level(level), bsf(NULL) { }
	~FilterBright();

	void Apply(Screen const& screen, Options const& opt) const;

private:
	void InitBacksurface(Screen const& screen) const;

	const double level;
	mutable uint8_t* bsf;
};

#endif

