#include "pointhash.h"

#include <stdlib.h>

PointHash* pointhash_init()
{
	PointHash* ph = malloc(sizeof(PointHash));
	ph->n_points = 0;
	ph->point = NULL;
	ph->data = NULL;
	return ph;
}


void pointhash_add(PointHash* ph, Point p, void* data, void(*freefunc)(void*))
{
	for(int i=0; i<ph->n_points; i++)
		if(ph->point[i].x == p.x && ph->point[i].y == p.y)
		{
			if(freefunc && ph->data[i])
				freefunc(ph->data[i]);
			ph->data[i] = data;
			return;
		}

	ph->point = realloc(ph->point, sizeof(Point) * (ph->n_points+1));
	ph->data = realloc(ph->data, sizeof(void*) * (ph->n_points+1));
	ph->point[ph->n_points] = p;
	ph->data[ph->n_points] = data;
	++ph->n_points;
}


void pointhash_del(PointHash* ph, Point p)
{
	for(int i=0; i<ph->n_points; i++)
		if(ph->point[i].x == p.x && ph->point[i].y == p.y)
			ph->data[i] = NULL;
}


void* pointhash_find(PointHash* ph, Point p)
{
	for(int i=0; i<ph->n_points; i++)
		if(ph->point[i].x == p.x && ph->point[i].y == p.y)
			return ph->data[i];
	return NULL;
}


void pointhash_free(PointHash* ph, void(*freefunc)(void*))
{
	if(freefunc)
		for(int i=0; i<ph->n_points; i++)
			if(ph->data[i])
				freefunc(ph->data[i]);
	if(ph->n_points > 0)
	{
		free(ph->point);
		free(ph->data);
	}
	free(ph);
}
