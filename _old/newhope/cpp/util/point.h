#ifndef POINT_H
#define POINT_H

#include <cmath>

template <typename T> int sgn(T val) { return (T(0) < val) - (val < T(0)); }

template <typename T>
class Point {
public:
	T x, y;
	mutable int elevation;
	//mutable std::map<Point, int> distances;
	
	Point() : Point(0, 0) { }
	Point(T x, T y) : x(x), y(y), elevation(0) { }

	Point (const Point& other) :
		x(other.x), y(other.y), elevation(other.elevation) { }
	
	Point& operator=(const Point& other)
	{
		if(this != &other) {
			x = other.x;
			y = other.y;
			elevation = other.elevation;
		}
		return *this;
	}


	inline T Distance(Point p2) const
	{
		/*
		if(distances.find(p2) != distances.end())
			distances[p2] = sqrt(pow(p2.x-x, 2) + pow(p2.y-y, 2));
		return distances[p2];
		*/
		return sqrt(pow(p2.x-x, 2) + pow(p2.y-y, 2));
	}

	inline Point Displace(Point p2, int displ) const
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
};

#endif
