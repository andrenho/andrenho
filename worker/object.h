#ifndef OBJECT_H
#define OBJECT_H

#include "util.h"

typedef enum { WORKER, BOX } ObjectType;

typedef struct Object {
	ObjectType object;
	int x, y;
	Direction dir;
	struct Object* next;
} Object;

#endif
