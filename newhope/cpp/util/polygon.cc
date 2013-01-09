#include "util/polygon.h"

#include <cstdlib>

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
