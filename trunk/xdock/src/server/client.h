#ifndef CLIENT_H
#define CLIENT_H

#include "structures.h"
#include "network.h"
#include "x11.h"

extern Client* clients;

Client* client_add();
void client_destroy(Client* client);

#endif
