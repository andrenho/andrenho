#ifndef WINDOW_H
#define WINDOW_H

#include "parser.h"

void wm_initialize();
void wm_execute(CommandQueue** queue);
void wm_quit();

#endif
