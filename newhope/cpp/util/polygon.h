#ifndef UTIL_POLYGON_H
#define UTIL_POLYGON_H

#include <climits>
#include <cmath>
#include <vector>

#include "util/rect.h"
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

	const struct Point Midpoint() const;
	void MidlineDisplacement(int n);
	void Debug() const;
	void NeighbourPoints(Point p, std::vector<Point>& neigh_points) const;
	bool ContainsPoint(Point p) const;
	bool IsTouching(Polygon const& p);
	bool BorderIntersects(Rect const& r);
	void CalculateLimits() const;

	static void FakeVoronoi(unsigned int seed, int w, int h, int density,
			std::vector<Polygon*>& polygons);

	std::vector<Point> points;

private:
	mutable int limit_x1, limit_y1, limit_x2, limit_y2;
	mutable Point midpoint;

public:
	inline bool PointInPolygon(Point p) const
	{
		// prefilter
		if(p.x < limit_x1 || p.y < limit_y1 || p.x > limit_x2 || p.y > limit_y2)
			return false;

		// prepare
		int nvert = points.size();
		float vertx[nvert], verty[nvert];
		int i = 0;
		for(const auto& point: points)
		{
			vertx[i] = point.x;
			verty[i++] = point.y;
		}
		float testx = p.x, testy = p.y;

		int j, c = 0;
		for (i = 0, j = nvert-1; i < nvert; j = i++)
			if ( ((verty[i]>testy) != (verty[j]>testy)) && (testx < (vertx[j]-vertx[i]) * (testy-verty[i]) / (verty[j]-verty[i]) + vertx[i]) )
				c = !c;
		return c;
	}



};

#endif
