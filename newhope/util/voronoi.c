#include "voronoi.h"

#include <stdio.h>
#include <stdlib.h>


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
	for(x=0; x<(max_x-1); x++)
		for(y=0; y<(max_y-1); y++)
		{
			Polygon* polygon = malloc(sizeof(Polygon*));
			polygon->n_segments = 4;
			polygon->segments = malloc(sizeof(Segment*));
			polygon->segments[0].p1 = points[x][y];
			polygon->segments[0].p2 = points[x+1][y];
			polygon->segments[1].p1 = points[x+1][y];
			polygon->segments[1].p2 = points[x+1][y+1];
			polygon->segments[2].p1 = points[x+1][y+1];
			polygon->segments[2].p2 = points[x][y+1];
			polygon->segments[3].p1 = points[x][y+1];
			polygon->segments[3].p2 = points[x][y];
			n_polygons++;
			*polygons = realloc(*polygons, sizeof(Polygon) * n_polygons);
		}
	
	return n_polygons;
}


int main()
{
	Polygon* polygons = NULL;
	int n = fake_voronoi(1, 500, 500, 5, &polygons);

	int i, j;
	for(i=0; i<n; i++)
	{
		printf("Polygon %d:\n", i);
		for(j=0; j<polygons[i].n_segments; j++)
			printf("%d %d - %d %d\n", 
					polygons[i].segments[j].p1.x,
					polygons[i].segments[j].p1.y,
					polygons[i].segments[j].p2.x,
					polygons[i].segments[j].p2.y);
	}

	return 0;
}

// gcc -Wall -g voronoi.c -o voronoi2 && ./voronoi2
