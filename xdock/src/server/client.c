#include "client.h"
#include "network.h"
#include "debug.h"
#include "parser.h"
#include "x11.h"

#include <stdlib.h>

Client* clients = NULL;


Client* client_add()
{
	debug("New client added.");

	// create new client
	Client* new_client = malloc(sizeof(Client));
	new_client->id[0] = '\0';

	// add client to the list
	if(clients == NULL)
		clients = new_client;
	else
	{
		Client* c = clients;
		while(c->next != NULL)
			c = c->next;
		c->next = new_client;
	}
	new_client->next = NULL;

	// initialize client on the WM
	x11_setup_client(new_client);

	return new_client;
}


void client_destroy(Client* client)
{
	// kills connection with client and X11
	net_disconnect_client(client->socket_fd);
	x11_destroy_client(client);

	// remove from list
	if(client != clients)
	{
		Client* c = clients;
		while(c && c->next != client)
			c = c->next;
		c->next = client->next;
	}
	else
		clients = client->next;

	free(client);
}
