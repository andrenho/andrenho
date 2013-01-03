#ifndef VORONOI_H
#define VORONOI_H

typedef struct Point {
	int x, y;
} Point;

typedef struct Segment {
	int n_points;
	Point* points;
} Polygon;

void fake_voronoi(unsigned int seed, int w, int h, int density);

#endif
