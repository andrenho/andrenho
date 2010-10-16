#include "window.h"

#include <stdlib.h>

static Client* client = NULL;


void win_create()
{
}


void win_loop_events()
{
	for(;;);
}


Client* win_new_client(int socket_fd)
{
	// create new client
	Client* new_client = malloc(sizeof(Client));
	new_client->socket_fd = socket_fd;

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


void win_remove_client(Client* c)
{
}
