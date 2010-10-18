#ifndef CLIENT_H
#define CLIENT_H

#include "network.h"

typedef struct Client {
	ClientNetwork net;
	struct Client* next;
} Client;

extern Client* clients;

Client* client_add(void* v_socket_fd);

#endif
