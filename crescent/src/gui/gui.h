#ifndef GUI_H
#define GUI_H

typedef enum { MAP, QUIT } GUI_STATE;
extern GUI_STATE gui_state;

int gui_init();

#endif
