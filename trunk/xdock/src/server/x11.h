#ifndef X11_H
#define X11_H

#include "parser.h"
#include "client.h"

void x11_initialize();
int x11_setup_client(Client* client);
void x11_destroy_client(Client* client);
void x11_quit();

// commands
int x11_draw_panel(Client* client, int x1, int x2, int y1, int y2);

#endif

