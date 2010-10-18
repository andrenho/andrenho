#include "client.h"
#include "network.h"

#include <stdlib.h>

Client* clients = NULL;

Client* client_add(void* v_socket_fd)
{
	// create new client
	Client* new_client = malloc(sizeof(Client));
	new_client->net.socket_fd = socket_fd;
	new_client->net.authorized = 0;

	// add client to the list
	if(client == NULL)
		client = new_client;
	else
	{
		Client* c = client;
		while(c->next != NULL)
			c = c->next;
		c->next = new_client;
	}

	return new_client;
}
