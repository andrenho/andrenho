#include "level.h"

#include <stdlib.h>

#include "levels.h"


static void initialize_structures(Level* lv, int n);


Level* level_load(int n)
{
	Level* lv = malloc(sizeof(Level));
	initialize_structures(lv, n);
	return lv;
}


void level_free(Level** lv)
{
	Structure* st = (*lv)->structures;
	while(!st)
	{
		Structure* next = st->next;
		free(st);
		st = next;
	}
	free(*lv);
	*lv = NULL;
}


static void initialize_structures(Level* lv, int n)
{
	int x, y;
	Structure* last_st = NULL;

	for(x=0; x<levels[n].w; x++)
		for(y=0; y<levels[n].h; y++)
		{
			Structure* st = malloc(sizeof(Structure));
			if(!last_st)
				lv->structures = st;
			else
				last_st->next = st;
			st->structure = levels[n].map[y][x];
			st->x = x;
			st->y = y;
			st->dir = RIGHT; // TODO
			st->next = NULL;
			last_st = st;
		}
}
