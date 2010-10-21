#ifndef NETWORK_H
#define NETWORK_H

typedef struct {
	int socket_fd;
	int authorized;
	char unprocessed_data[4096];
} ClientNetwork;

void net_startup();
void net_check_for_clients();
void net_receive_data();
void net_disconnect_client(int socket_fd);
void net_quit();

#endif
