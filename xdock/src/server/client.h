#ifndef CLIENT_H
#define CLIENT_H

#include "network.h"

typedef struct Client {
	ClientNetwork net;
	struct Client* next;
} Client;

extern Client* clients;

void client_add(int socket_fd);

#endif
