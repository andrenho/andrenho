#include "util/polygon.h"

#include <cstdlib>
#include <vector>

#include "util/logger.h"

Polygon::Polygon(struct Point* points, int n_points)
	: Polygon()
{
	for(int i=0; i<n_points; i++)
		this->points.push_back(points[i]);
}


Polygon::Polygon(Rect r)
	: Polygon()
{
	points.push_back({ r.x, r.y });
	points.push_back({ (r.x+r.w), r.y });
	points.push_back({ (r.x+r.w), (r.y+r.h) });
	points.push_back({ r.x, (r.y+r.h) });
}


bool 
Polygon::ContainsPoint(Point p) const
{
	// prefilter
	if(limit_x1 == INT_MAX)
		CalculateLimits();
	if(p.x < limit_x1 || p.y < limit_y1 || p.x > limit_x2 || p.y > limit_y2)
		return false;

	// prepare
	int i=0;
	int polySides = points.size();
	float polyX[polySides],
	      polyY[polySides];

	for(std::vector<Point>::const_iterator point = points.begin(); 
			point != points.end(); point++)
	{
		polyX[i] = (*point).x;
		polyY[i] = (*point).y;
		++i;
	}
	
	// calculate
	int j=polySides-1;
	int oddNodes = 0;

	for(i=0; i<polySides; i++)
	{
		if((polyY[i] < p.y && polyY[j] >= p.y
		||  polyY[j] < p.y && polyY[i] >= p.y)
		&& (polyX[i] <= p.x || polyX[j] <= p.x))
			oddNodes ^= (polyX[i] + (p.y - polyY[i]) /
						(polyY[j] - polyY[i]) *
						(polyX[j] - polyX[i]) < p.x);
		j = i;
	}

	return oddNodes != 0;
}


void Polygon::FakeVoronoi(unsigned int seed, int w, int h, int density, 
		std::vector<Polygon*>& polygons)
{
	int x, y;
	int xx, yy;

	// initialize seed
	srand(seed);

	// add points
	int n_points = 0, max_x = 0,max_y = 0;
	struct Point points[density][density];
	for(x=0, xx=0; x<w; x+=(w/density))
	{
		for(y=0, yy=0; y<h; y+=(h/density))
			if(x > 0 && y > 0)
			{
				points[xx][yy++] = (struct Point) { x, y };
				n_points++;
			}
		max_y = yy;
		if(x > 0)
			xx++;
	}
	max_x = xx;

	// disturb points
	int max_disturb = (w/density/2);
	for(x=0; x<max_x; x++)
		for(y=0; y<max_y; y++)
		{
			points[x][y].x += (rand() % max_disturb) - max_disturb/2;
			points[x][y].y += (rand() % max_disturb) - max_disturb/2;
		}

	// generate polygons
	for(x=0; x<(max_x-1); x++)
		for(y=0; y<(max_y-1); y++)
		{
			polygons.push_back(new Polygon());
			polygons.back()->points.push_back(points[x][y]);
			polygons.back()->points.push_back(points[x+1][y]);
			polygons.back()->points.push_back(points[x+1][y+1]);
			polygons.back()->points.push_back(points[x][y+1]);
		}
}


const struct Point 
Polygon::Midpoint() const
{
	if(limit_x1 == INT_MAX)
		CalculateLimits();
	return (const struct Point) {
		limit_x1 + (limit_x2 - limit_x1) / 2,
		limit_y1 + (limit_y2 - limit_y1) / 2
	};
}


void 
Polygon::CalculateLimits() const
{
	limit_x1 = limit_y1 = INT_MAX;
	limit_x2 = limit_y2 = 0;

	for(std::vector<Point>::const_iterator point = points.begin(); 
			point != points.end(); point++)
	{
		int x = (*point).x;
		if(x < limit_x1)
			limit_x1 = x;
		if(x > limit_x2)
			limit_x2 = x;

		int y = (*point).y;
		if(y < limit_y1)
			limit_y1 = y;
		if(y > limit_y2)
			limit_y2 = y;
	}
}


void 
Polygon::MidlineDisplacement(int n)
{
	if(n == 0)
		CalculateLimits();
	else
	{
		std::vector<Point> new_points;
		for(std::vector<Point>::const_iterator point = points.begin(); 
				point != points.end(); point++)
		{
			Point p1 = *point;
			Point p2 = points.front();
			if(point+1 != points.end())
				p2 = *(point+1);
			Point p3 = p1.Displace(p2, 6);
			new_points.push_back(p1);
			new_points.push_back(p3);
		}
		points.swap(new_points);
		
		MidlineDisplacement(n-1);
	}
}


void
Polygon::Debug() const
{
	for(std::vector<Point>::const_iterator point = points.begin(); 
			point != points.end(); point++)
	{
		logger.Debug("%d %d", (*point).x, (*point).y);
	}
}
