#include "level.h"

#include <stdlib.h>

#include "levels.h"


static void initialize_structures(Level* lv, int n);
static void init_object(Level* lv, ObjectType ot, int x, int y, Direction dir);


Level* level_load(int n)
{
	Level* lv = malloc(sizeof(Level));
	lv->objects = NULL;
	initialize_structures(lv, n);
	return lv;
}


void level_reset(Level* lv)
{
	Structure* st = lv->structures;
	do
	{
		switch(st->structure)
		{
		case ENTRANCE:
			init_object(lv, WORKER, st->x, st->y, RIGHT);
			break;
		case BOXSTART:
			init_object(lv, WORKER, st->x, st->y, RIGHT);
			break;
		default:
			;
		}
	} while((st = st->next));
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


static void init_object(Level* lv, ObjectType ot, int x, int y, Direction dir)
{
	Object* on = malloc(sizeof(Object));
	on->object = ot;
	on->x = x;
	on->y = y;
	on->dir = dir;
	on->next = NULL;

	if(!lv->objects)
		lv->objects = on;
	else
	{
		Object* o = lv->objects;
		while(o->next)
			o = o->next;
		o->next = on;
	}
}
