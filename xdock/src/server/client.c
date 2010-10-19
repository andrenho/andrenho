#include "client.h"
#include "network.h"
#include "debug.h"
#include "x11.h"

#include <stdlib.h>

Client* clients = NULL;


static void client_main_loop(Client* c);


void client_add(int socket_fd)
{
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
	x11_setup_client(new_client);

	// client main loop
	client_main_loop(new_client);

	// destroy the client on the WM
	net_disconnect_client(new_client->net.socket_fd);
	x11_destroy_client(new_client);

	free(new_client);
}


static void client_main_loop(Client* c)
{
	// receive data and update client
	while(net_receive_client_data(&c->net))
	{
		if(!parse_data(c->net.unprocessed_data, c))
		{
			// TODO - warn client of syntax error
			break;
		}

		// check for events and send data to client
		// TODO

	}
}
