#include "client.h"
#include "network.h"
#include "debug.h"

#include <stdlib.h>

Client* clients = NULL;


static void client_main_loop(Client* c);


void client_add(int socket_fd)
{
	debug("Server", "New client added.");

	// create new client
	Client* new_client = malloc(sizeof(Client));
	new_client->net.socket_fd = socket_fd;
	new_client->net.authorized = 0;
	new_client->net.unprocessed_data.length = 0;
	new_client->command_queue = NULL;

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

	client_main_loop(new_client);
}


static void client_main_loop(Client* c)
{
	// receive data and update client
	net_receive_client_data(&c->net);
	parse_data(&c->net.unprocessed_data, &c->command_queue);
	wm_execute(&c->command_queue);

	// check for events and send data to client
}
