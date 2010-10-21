#ifndef CLIENT_H
#define CLIENT_H

#include "network.h"
#include "x11.h"

typedef struct Client {
	ClientNetwork net;
	WM wm;
	struct Client* next;
} Client;

extern Client* clients;

void client_add(int socket_fd);
void client_destroy(Client* client);

#endif
