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
	Point midpoint;
} Polygon;

int point_in_polygon(Point p, Polygon* polygon);
int fake_voronoi(unsigned int seed, int w, int h, int density, Polygon*** polygons);
Polygon* create_polygon(int n_points, Point* point);
Polygon* midline_displacement(Polygon* polygon, int iters);
void free_polygon(Polygon* polygon);

#endif
