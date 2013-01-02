#ifndef NUMBERS_H
#define NUMBERS_H

int imin(int a, int b);
int imax(int a, int b);
int sgn(int a);
int point_in_polygon(int polySides, float* polyX, float* polyY, 
		float x, float y);
// http://rosettacode.org/wiki/Voronoi_diagram
void voronoi();

#endif
