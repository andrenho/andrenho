#ifndef FILTER_INEXACT_H
#define FILTER_INEXACT_H

#include "filter.h"

class FilterInexact : public Filter
{
public:
	~FilterInexact() { }
	void Apply(Screen const& screen) const;

private:
	static const int LEVEL = 10;
};

#endif
