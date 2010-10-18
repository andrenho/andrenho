#ifndef WINDOW_H
#define WINDOW_H

#include "parser.h"
#include "client.h"

void wm_initialize();
void wm_setup_client(Client* client);
void wm_execute(CommandQueue** queue);
void wm_destroy_client(Client* client);
void wm_quit();

#endif
