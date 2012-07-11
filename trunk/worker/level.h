#ifndef LEVEL_H
#define LEVEL_H

#include "structure.h"

typedef struct {
	Structure* structures;
} Level;

Level* level_load(int n);
void level_free(Level** lv);

#endif
