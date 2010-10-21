#include "client.h"
#include "network.h"
#include "debug.h"
#include "parser.h"
#include "x11.h"

#include <stdlib.h>

Client* clients = NULL;


void client_add(int socket_fd)
{
	debug("Server", "New client added.");

	// create new client
	Client* new_client = malloc(sizeof(Client));
	new_client->net.socket_fd = socket_fd;
	new_client->net.authorized = 0;
	new_client->net.unprocessed_data[0] = '\0';

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

	// initialize client on the WM
	x11_setup_client(&new_client->wm);
}


void client_destroy(Client* client)
{
	// kills connection with client and X11
	net_disconnect_client(client->net.socket_fd);
	x11_destroy_client(&client->wm);

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
