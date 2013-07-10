#ifndef LEVEL_H
#define LEVEL_H

#include "structure.h"
#include "object.h"

typedef struct {
	Structure* structures;
	Object* objects;
} Level;

Level* level_load(int n);
void level_reset(Level* lv);
void level_free(Level** lv);

#endif
