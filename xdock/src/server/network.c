#include "network.h"

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <unistd.h>
#include <resolv.h>
#include <pthread.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#include "options.h"
#include "debug.h"
#include "window.h"
#include "parser.h"


static int sock; // main communication socket


// send data to client
static void inline say(int socket_fd, char* fmt, ...)
{
	va_list ap;
	char data[4096];

	va_start(ap, fmt);
	int sz = vsprintf(data, fmt, ap);
	va_end(ap);

	data[sz] = '\n'; // trailing eol
	sz++;

	ssize_t written = 0;
	do
		written += send(socket_fd, &data[written], sz - written, 0);
	while(written < sz);
}


// This thread is created when a new client connects.
static void *net_new_client(void* v_socket_fd)
{
	size_t bytes;
	char input[4096];
	int socket_fd = (int)(long)v_socket_fd;
	
	debug("Server", "Client connected to socket %d.", socket_fd);

	// create client
	Client* client = win_new_client(socket_fd);

	// say hello
	say(client->socket_fd, "HELLO xdockserver 0.3.0"); // TODO - version

	// listen
	bytes = 1;
	while(bytes != 0)
	{
		bytes = recv(client->socket_fd, input, 4096, 0);
		parse_input(client, input, bytes);
	}

	// remove client
	win_remove_client(client);

	return NULL;
}


// This thread waits for new client connections.
static void *net_accept_connections(void* v_sock)
{
	struct sockaddr_in client_address;
	unsigned int client_address_length;
	pthread_t* thread;
	sock = (int)(long)v_sock;

	// accept incoming connections
	for(;;)
	{
		client_address_length = sizeof(client_address);
		int socket_fd = accept(sock, (struct sockaddr*)&client_address, 
				&client_address_length);
		thread = malloc(sizeof(pthread_t));
		pthread_create(thread, NULL, net_new_client, 
				(void*)(long)socket_fd);
	}

	return NULL;
}


// Initialize network and open port.
void net_startup()
{
	static int sock;
	struct sockaddr_in address;
	pthread_t thread;

	// create socket
	if((sock = socket(AF_INET, SOCK_STREAM, 0)) == -1)
	{
		fprintf(stderr, "Error opening socket.\n");
		exit(1);
	}

	// choose who the server is going to list to
	address.sin_family = AF_INET;
	address.sin_addr.s_addr = INADDR_ANY;
	if(opt.listen_to == LOCALHOST) // only localhost
		if(!inet_aton("127.0.0.1", &address.sin_addr))
		{
			fprintf(stderr, "It was not possible to get localhost "
					"address.\n");
			exit(1);
		}
	address.sin_port = htons(52530);

	// bind socket
	if(bind(sock, (struct sockaddr*)&address, sizeof(address)) < 0)
	{
		fprintf(stderr, "Can't bind socket.\n");
		exit(1);
	}

	// listen on socket
	listen(sock, 5);
	debug("Server", "Network initialized, waiting connections.");

	pthread_create(&thread, NULL, net_accept_connections, 
			(void*)(long)sock);
}


void net_quit()
{
	Client* c = client;
	while(c != NULL)
	{
		close(c->socket_fd);
		c = c->next;
	}
	close(sock);
}
