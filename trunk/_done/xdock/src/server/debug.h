#ifndef DEBUG_H
#define DEBUG_H

#include "structures.h"

typedef enum { FROM, TO } Direction;

void debug(char* fmt, ...);
void debug_comm(Client* c, Direction dir, char* fmt, ...);

#endif
