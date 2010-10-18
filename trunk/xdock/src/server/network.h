#ifndef NETWORK_H
#define NETWORK_H

typedef struct {
	char data[4096];
	int length;
} UnprocessedData;

typedef struct {
	int socket_fd;
	int authorized;
	UnprocessedData unprocessed_data;
} ClientNetwork;

void net_startup();
void net_receive_client_data(ClientNetwork *net);
void net_quit();

#endif
