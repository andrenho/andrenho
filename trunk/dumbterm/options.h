#ifndef OPTIONS_H
#define OPTIONS_H

#include <vector>
using namespace std;

#include "filter.h"

class Options
{
public:
	Options() : scale(2), w(80), h(25) { }
	inline vector<Filter> const Filters() const { return filters; }

	const int scale;
	const int w, h;

private:
	vector<Filter> const filters;
};

#endif
