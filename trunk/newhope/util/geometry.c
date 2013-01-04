#include "geometry.h"

#include <limits.h>
#include <stdio.h>
#include <stdlib.h>


static void find_polygon_limits(Polygon* polygon);


int point_in_polygon(int polySides, float* polyX, float* polyY, 
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
	Polygon* polygon = NULL;
	int n_polygons = 0;
	for(x=0; x<(max_x-1); x++)
		for(y=0; y<(max_y-1); y++)
		{
			polygon = realloc(polygon, 
					sizeof(Polygon) * (n_polygons + 1));
			polygon[n_polygons].n_segments = 4;
			polygon[n_polygons].segments = malloc(sizeof(Segment) * 4);
			polygon[n_polygons].segments[0].p1 = points[x][y];
			polygon[n_polygons].segments[0].p2 = points[x+1][y];
			polygon[n_polygons].segments[1].p1 = points[x+1][y];
			polygon[n_polygons].segments[1].p2 = points[x+1][y+1];
			polygon[n_polygons].segments[2].p1 = points[x+1][y+1];
			polygon[n_polygons].segments[2].p2 = points[x][y+1];
			polygon[n_polygons].segments[3].p1 = points[x][y+1];
			polygon[n_polygons].segments[3].p2 = points[x][y];
			find_polygon_limits(&polygon[n_polygons]);
			n_polygons++;
		}
	
	*polygons = polygon;
	return n_polygons;
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
}
