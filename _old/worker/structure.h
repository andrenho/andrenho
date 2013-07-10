#ifndef STRUCTURE_H
#define STRUCTURE_H

#include "util.h"

typedef struct Structure {
	enum { 
		ENTRANCE='1', DOOR='#', WALL='.', BOXSTART='X',
	} structure;
	int x, y;
	Direction dir;
	struct Structure* next;
} Structure;

#endif
