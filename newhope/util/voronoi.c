#include "voronoi.h"

#include <stdio.h>
#include <stdlib.h>


void fake_voronoi(unsigned int seed, int w, int h, int density)
{
	int i, x, y;

	// initialize seed
	srand(seed);

	// add points
	int n_points = 0;
	Point points[density*density];
	for(x=0; x<w; x+=(w/density))
		for(y=0; y<h; y+=(h/density))
			if(x > 0 && y > 0)
				points[n_points++] = (Point) { x, y };

	// disturb points
	int max_disturb = (w/density/2);
	for(i=0; i<n_points; i++)
	{
		points[i].x += (rand() % max_disturb) - max_disturb/2;
		points[i].y += (rand() % max_disturb) - max_disturb/2;
	}

	// generate polygons
	

	for(i=0; i<n_points; i++)
		printf("%d %d\n", points[i].x, points[i].y);
}


int main()
{
	fake_voronoi(1, 500, 500, 5);

	return 0;
}

// gcc -Wall -g voronoi.c -o voronoi2 && ./voronoi2
