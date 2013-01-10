#ifndef UTIL_POLYGON_H
#define UTIL_POLYGON_H

#include <climits>
#include <cmath>
#include <vector>

#include "libs/rect.h"

template <typename T> int sgn(T val) { return (T(0) < val) - (val < T(0)); }

struct Point {
	int x, y;

	inline int Distance(struct Point p2) const
	{
		return sqrt(pow(p2.x-x, 2) + pow(p2.y-y, 2));
	}

	inline struct Point Displace(struct Point p2, int displ) const
	{
		int mx = (x+p2.x)/2,
		    my = (y+p2.y)/2;
		int dx = (p2.y-y) / 4;
		int dy = (x-p2.x) / 4;
		return { mx+dx, my+dy };
	}
};


class Polygon 
{
public:
	Polygon() : 
		limit_x1(INT_MAX), limit_y1(INT_MAX), limit_x2(0), limit_y2(0)
	{ }
	Polygon(struct Point* points, int n_points);
	Polygon(Rect r);

	bool ContainsPoint(Point p) const;
	const struct Point Midpoint() const;
	void MidlineDisplacement(int n);
	void Debug() const;

	static void FakeVoronoi(unsigned int seed, int w, int h, int density,
			std::vector<Polygon*>& polygons);

	std::vector<Point> points;

private:
	void CalculateLimits() const;

	mutable int limit_x1, limit_y1, limit_x2, limit_y2;
	mutable Point midpoint;
};

#endif
