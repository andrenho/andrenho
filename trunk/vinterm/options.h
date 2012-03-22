#ifndef OPTIONS_H
#define OPTIONS_H

#include <vector>
using namespace std;

class Filter;

class Options
{
public:
	Options();
	~Options();

	inline vector<Filter*>* Filters() { return &filters; }

	const int scale;
	const int w, h;

private:
	vector<Filter*> filters;
};

#endif
