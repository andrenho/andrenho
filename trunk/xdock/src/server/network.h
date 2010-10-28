#ifndef NETWORK_H
#define NETWORK_H

#include "structures.h"

void net_startup();
void net_check_for_clients();
void net_receive_data();
int net_send_client_data(Client* c, char* fmt, ...);
void net_disconnect_client(int socket_fd);
void net_quit();

#endif
