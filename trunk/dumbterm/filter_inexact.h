#ifndef FILTER_INEXACT_H
#define FILTER_INEXACT_H

#include <cstdio>
#include "filter.h"

class FilterInexact : public Filter
{
public:
	~FilterInexact() { printf("Destroy\n"); }
	void Apply(Screen const& screen);

private:
	static const int LEVEL = 30;
};

#endif
