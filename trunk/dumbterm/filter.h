#ifndef FILTER_H
#define FILTER_H

#include "screen.h"

class Filter
{
public:
	virtual ~Filter() { }
	virtual void Apply(Screen const& screen) const = 0;
};

#endif
