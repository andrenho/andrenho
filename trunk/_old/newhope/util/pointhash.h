#ifndef POINTHASH_H
#define POINTHASH_H

#include "util/geometry.h"

// TODO - brute force hash - slow performace!!!

typedef struct PointHash {
	int n_points;
	Point* point;
	void** data;
} PointHash;

PointHash* pointhash_init();
void pointhash_add(PointHash* ph, Point p, void* data, void(*freefunc)(void*));
void pointhash_del(PointHash* ph, Point p);
void* pointhash_find(PointHash* ph, Point p);
void pointhash_free(PointHash* ph, void(*freefunc)(void*));

#endif
