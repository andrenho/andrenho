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


int fake_voronoi(unsigned int seed, int w, int h, int density, Polygon*** polygons)
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
	int i = 0; 
	int n_polygons = (max_x-1) * (max_y-1);
	*polygons = calloc(sizeof(Polygon*), n_polygons);
	for(x=0; x<(max_x-1); x++)
		for(y=0; y<(max_y-1); y++)
		{
			Point pts[] = {	points[x][y], points[x+1][y], 
				points[x+1][y+1], points[x][y+1] };
			Polygon* polygon = create_polygon(4, pts);
			(*polygons)[i++] = polygon;
		}
	
	return n_polygons;
}


Polygon* create_polygon(int n_points, Point* point)
{
	int i;
	
	Polygon* polygon = calloc(sizeof(Polygon), 1);
	polygon->n_segments = n_points;
	polygon->segments = calloc(sizeof(Segment), n_points);
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


void free_polygon(Polygon* polygon)
{
	if(polygon->segments)
		free(polygon->segments);
	free(polygon);
}


Polygon* midline_displacement(Polygon* polygon, int iters)
{
	if(iters == 0)
	{
		find_polygon_limits(polygon);
		return polygon;
	}
	else
	{
		int pi = 0;
		int n_segs = polygon->n_segments * 2;
		Point points[n_segs];

		int i;
		for(i=0; i<polygon->n_segments; i++)
		{
			Point p1 = polygon->segments[i].p1,
			      p2 = polygon->segments[i].p2;

			Point mid = {
				p1.x + (p2.x - p1.x) / 2,
				p1.y + (p2.y - p1.y) / 2
			};

			int displ = rand() % ((p2.x - p1.x) / 3 + 1);
			if(i == 0)
				mid.y -= displ;
			else if(i == 1)
				mid.x += displ;
			else if(i == 2)
				mid.y += displ;
			else if(i == 3)
				mid.x -= displ;

			points[pi++] = p1;
			points[pi++] = mid;
		}

		Polygon* new_p = create_polygon(n_segs, points);
		free_polygon(polygon);
		return midline_displacement(new_p, iters-1);
	}
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

