#ifndef OPTIONS_H
#define OPTIONS_H

#include "structures.h"

// The list of the user options. This structure is in structures.h.
extern Options opt;

void opt_parse(int argc, char* argv[]);

#endif
