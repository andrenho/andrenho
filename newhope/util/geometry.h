#ifndef GEOMETRY_H
#define GEOMETRY_H

typedef struct Point {
	int x, y;
} Point;

typedef struct Segment {
	Point p1, p2;
} Segment;

typedef struct Polygon {
	int n_segments;
	Segment* segments;
	int limit_x1, limit_x2, limit_y1, limit_y2;
} Polygon;

int point_in_polygon(int polySides, float* polyX, float* polyY, 
		float x, float y);
int fake_voronoi(unsigned int seed, int w, int h, int density, Polygon** polygons);
void free_polygon(Polygon* polygon);

#endif
