#ifndef GUI_H
#define GUI_H

#include <stdbool.h>

#define SCREEN_W 80
#define SCREEN_H 50

typedef enum { MAP, QUIT } GUI_STATE;
extern GUI_STATE gui_state;
extern bool color;

int gui_init();

#endif
