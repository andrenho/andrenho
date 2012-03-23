#ifndef OPTIONS_H
#define OPTIONS_H

#include <vector>
#include "SDL.h"
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
	const int border_x, border_y;
	const SDL_Color background_color, bright_color;

private:
	vector<Filter*> filters;
};

#endif
