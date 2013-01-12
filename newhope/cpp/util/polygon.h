#ifndef UTIL_POLYGON_H
#define UTIL_POLYGON_H

#include <climits>
#include <cmath>
#include <vector>

#include "libs/rect.h"
#include "util/point.h"

class Polygon 
{
public:

	Polygon() : 
		limit_x1(INT_MAX), limit_y1(INT_MAX), limit_x2(0), limit_y2(0),
		midpoint({ -1, -1})
	{ }
	Polygon(struct Point* points, int n_points);
	Polygon(Rect r);

	bool PointInPolygon(Point p) const;
	const struct Point Midpoint() const;
	void MidlineDisplacement(int n);
	void Debug() const;
	void NeighbourPoints(Point p, std::vector<Point>& neigh_points) const;
	bool ContainsPoint(Point p) const;
	bool IsTouching(Polygon const& p);

	static void FakeVoronoi(unsigned int seed, int w, int h, int density,
			std::vector<Polygon*>& polygons);

	std::vector<Point> points;

private:
	void CalculateLimits() const;

	mutable int limit_x1, limit_y1, limit_x2, limit_y2;
	mutable Point midpoint;
};

#endif
