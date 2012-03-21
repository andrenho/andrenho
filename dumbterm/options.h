#ifndef OPTIONS_H
#define OPTIONS_H

#include <vector>
using namespace std;

#include "filter.h"

class Options
{
public:
	Options() : scale(2), pw(400), ph(300) { }
	inline vector<Filter> const Filters() const { return filters; }

	const int scale;
	const int pw, ph;

private:
	vector<Filter> const filters;
};

#endif
