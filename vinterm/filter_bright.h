#ifndef FILTER_BRIGHT_H
#define FILTER_BRIGHT_H

#include <cstdio>
#include "filter.h"

class FilterBright : public Filter
{
public:
	FilterBright(double brightness=1, int sharpness=0) 
		: brightness(brightness), sharpness(sharpness), bsf(NULL) { }
	~FilterBright();

	void Apply(Screen const& screen, Options const& opt) const;
	inline FilterType Type() const { return PRE; }

private:
	void InitBacksurface(Screen const& screen) const;
	void ApplyPixel(Screen const& screen, int x, int y, int sp) const;

	const double brightness;
	const int sharpness;
	mutable uint8_t* bsf;
};

#endif

