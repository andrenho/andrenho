#ifndef VORONOI_H
#define VORONOI_H

typedef struct Point {
	int x, y;
} Point;

typedef struct Segment {
	Point p1, p2;
} Segment;

typedef struct Polygon {
	int n_segments;
	Segment* segments;
} Polygon;

int fake_voronoi(unsigned int seed, int w, int h, int density, Polygon** polygons);

#endif
