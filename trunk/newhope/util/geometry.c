#include "geometry.h"

#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


static void find_polygon_limits(Polygon* polygon);
static int point_in_polygon_algorithm(int polySides, float* polyX, float* polyY, 
		float x, float y);


int point_in_polygon(Point p, Polygon* polygon)
{
	int i;
	int polySides = polygon->n_segments;
	float polyX[polySides],
	      polyY[polySides];

	for(i=0; i<polySides; i++)
	{
		polyX[i] = polygon->segments[i].p1.x;
		polyY[i] = polygon->segments[i].p1.y;
	}
	return point_in_polygon_algorithm(polySides, polyX, polyY, p.x, p.y);
}


int fake_voronoi(unsigned int seed, int w, int h, int density, Polygon** polygons)
{
	int x, y;
	int xx, yy;

	// initialize seed
	srand(seed);

	// add points
	int n_points = 0, max_x = 0,max_y = 0;
	Point points[density][density];
	for(x=0, xx=0; x<w; x+=(w/density))
	{
		for(y=0, yy=0; y<h; y+=(h/density))
			if(x > 0 && y > 0)
			{
				points[xx][yy++] = (Point) { x, y };
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
	int n_polygons = 0;
	Polygon* ps = NULL;
	for(x=0; x<(max_x-1); x++)
		for(y=0; y<(max_y-1); y++)
		{
			Point pts[] = {	points[x][y], points[x+1][y], 
				points[x+1][y+1], points[x][y+1] };
			Polygon* polygon = create_polygon(4, pts);
			
			ps = realloc(ps, sizeof(Polygon) * (n_polygons + 1));
			memcpy(&ps[n_polygons], polygon, sizeof(Polygon));

			n_polygons++;
		}
	
	*polygons = ps;
	return n_polygons;
}


Polygon* create_polygon(int n_points, Point* point)
{
	int i;
	
	Polygon* polygon = calloc(sizeof(Polygon), 1);
	polygon->n_segments = n_points;
	polygon->segments = malloc(sizeof(Segment) * n_points);
	for(i=0; i<n_points; i++)
	{
		polygon->segments[i].p1 = point[i];
		if(i != (n_points-1))
			polygon->segments[i].p2 = point[i+1];
		else
			polygon->segments[i].p2 = point[0];
		find_polygon_limits(polygon);
	}
	return polygon;
}


Polygon* midline_displacement(Polygon* polygon, int iters)
{
	if(iters == 0)
		return polygon;
	else
	{
		return midline_displacement(polygon, iters-1);
	}
}


void free_polygon(Polygon* polygon)
{
	free(polygon->segments);
	free(polygon);
}


/*
 * STATIC
 */
static void find_polygon_limits(Polygon* polygon)
{
	int i;

	polygon->limit_x1 = polygon->limit_y1 = INT_MAX;
	polygon->limit_x2 = polygon->limit_y2 = 0;

	for(i=0; i<polygon->n_segments; i++)
	{
		int x = polygon->segments[i].p1.x;
		if(x < polygon->limit_x1)
			polygon->limit_x1 = x;
		if(x > polygon->limit_x2)
			polygon->limit_x2 = x;

		int y = polygon->segments[i].p1.y;
		if(y < polygon->limit_y1)
			polygon->limit_y1 = y;
		if(y > polygon->limit_y2)
			polygon->limit_y2 = y;

		x = polygon->segments[i].p2.x;
		if(x < polygon->limit_x1)
			polygon->limit_x1 = x;
		if(x > polygon->limit_x2)
			polygon->limit_x2 = x;

		y = polygon->segments[i].p2.y;
		if(y < polygon->limit_y1)
			polygon->limit_y1 = y;
		if(y > polygon->limit_y2)
			polygon->limit_y2 = y;
	}

	polygon->midpoint = (Point) {
		polygon->limit_x1 + (polygon->limit_x2 - polygon->limit_x1) / 2,
		polygon->limit_y1 + (polygon->limit_y2 - polygon->limit_y1) / 2
	};

}


static int point_in_polygon_algorithm(int polySides, float* polyX, float* polyY, 
		float x, float y)
{
	int i, j=polySides-1;
	int oddNodes = 0;

	for(i=0; i<polySides; i++)
	{
		if((polyY[i] < y && polyY[j] >= y
		||  polyY[j] < y && polyY[i] >= y)
		&& (polyX[i] <= x || polyX[j] <= x))
			oddNodes ^= (polyX[i] + (y - polyY[i]) /
						(polyY[j] - polyY[i]) *
						(polyX[j] - polyX[i]) < x);
		j = i;
	}

	return oddNodes;
}

