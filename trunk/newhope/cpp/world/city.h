#ifndef WORLD_CITY_H
#define WORLD_CITY_H

#include "util/point.h"

class City
{
public:
	City(Point point)
		: point(point) { }

	const Point point;
};

#endif
