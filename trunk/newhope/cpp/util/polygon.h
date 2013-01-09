#ifndef UTIL_POLYGON_H
#define UTIL_POLYGON_H

#include <vector>

struct Point {
	int x, y;
};


class Polygon 
{
public:
	static void FakeVoronoi(unsigned int seed, int w, int h, int density,
			std::vector<Polygon*>& polygons);

	std::vector<Point> points;
};

#endif
