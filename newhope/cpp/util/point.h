#ifndef POINT_H
#define POINT_H

#include <cmath>

template <typename T> int sgn(T val) { return (T(0) < val) - (val < T(0)); }

struct Point {
	int x, y;
	mutable int elevation;

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

	inline bool operator==(const Point& p) const {
		return x == p.x && y == p.y;
	}
};

#endif
