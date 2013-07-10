#ifndef OPTIONS_H
#define OPTIONS_H

#include "structures.h"

#define THEME_COLORS "panel_bg", "panel_lt", "panel_sw", "unlit", "halflit", \
	             "lit", "glow", "warning", "warning_unlit"

// The list of the user options. This structure is in structures.h.
extern Options opt;

void opt_parse(int argc, char* argv[]);

#endif
