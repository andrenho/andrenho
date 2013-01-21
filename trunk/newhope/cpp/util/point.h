#ifndef POINT_H
#define POINT_H

#include <cmath>

template <typename T> int sgn(T val) { return (T(0) < val) - (val < T(0)); }

// TODO - no need for two types of point! Convert to templates.

template <typename T>
struct Point {
	T x, y;
	mutable int elevation;
	//mutable std::map<Point, int> distances;
	
	inline T Distance(struct Point p2) const
	{
		/*
		if(distances.find(p2) != distances.end())
			distances[p2] = sqrt(pow(p2.x-x, 2) + pow(p2.y-y, 2));
		return distances[p2];
		*/
		return sqrt(pow(p2.x-x, 2) + pow(p2.y-y, 2));
	}

	inline struct Point Displace(struct Point p2, int displ) const
	{
		T mx = (x+p2.x)/2,
		    my = (y+p2.y)/2;
		T dx = (p2.y-y) / 4;
		T dy = (x-p2.x) / 4;
		return { mx+dx, my+dy };
	}

	inline bool operator==(const Point& p) const {
		return x == p.x && y == p.y;
	}

	inline bool operator<(const Point& p) const {
		return (y*10000+x) < (p.y*10000+p.x);
	}

	template<class F> operator Point<F>() const {
		return { static_cast<F>(x), static_cast<F>(y) };
	}

	/*
	inline operator DPoint() const {
		return DPoint { static_cast<double>(x), static_cast<double>(y) };
	}*/
};

typedef Point<int> IPoint;
typedef Point<double> DPoint;

/*
struct DPoint {
	double x, y;
};

struct Point {
	int x, y;
	mutable int elevation;
	//mutable std::map<Point, int> distances;
	
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

	inline bool operator<(const Point& p) const {
		return (y*10000+x) < (p.y*10000+p.x);
	}

	inline operator DPoint() const {
		return DPoint { static_cast<double>(x), static_cast<double>(y) };
	}
};*/


#endif
