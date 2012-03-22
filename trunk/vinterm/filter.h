#ifndef FILTER_H
#define FILTER_H

#include <cstdio>
#include "screen.h"

class Filter
{
public:
	virtual ~Filter() { }
	virtual void Apply(Screen const& screen, Options const& opt) const = 0;
};

#endif
