#ifndef FILTER_H
#define FILTER_H

#include <cstdio>
#include "screen.h"

class Filter
{
public:
	virtual ~Filter() { printf("Destroy\n"); }
	virtual void Apply(Screen const& screen) { printf("1\n") ; }
};

#endif
