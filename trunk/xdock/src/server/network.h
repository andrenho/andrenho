#ifndef NETWORK_H
#define NETWORK_H

typedef struct {
	int socket_fd;
	int authorized;
	char unprocessed_data[4096];
} ClientNetwork;

void net_startup();
int net_receive_client_data(ClientNetwork *net);
void net_disconnect_client(int socket_fd);
void net_quit();

#endif
