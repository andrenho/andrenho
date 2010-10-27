#ifndef CLIENT_H
#define CLIENT_H

#include "structures.h"
#include "network.h"
#include "x11.h"

extern Client* clients;

Client* client_add(int socket_fd);
void client_destroy(Client* client);

#endif
