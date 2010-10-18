#ifndef CLIENT_H
#define CLIENT_H

#include "network.h"
#include "parser.h"

typedef struct Client {
	ClientNetwork net;
	CommandQueue* command_queue;
	struct Client* next;
} Client;

extern Client* clients;

void client_add(int socket_fd);

#endif
