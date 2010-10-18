#ifndef NETWORK_H
#define NETWORK_H

typedef struct {
	int socket_fd;
	int authorized;
} ClientNetwork;

void net_startup();
void net_quit();

#endif
