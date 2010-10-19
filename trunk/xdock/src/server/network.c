#include "network.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include <unistd.h>
#include <errno.h>
#include <pthread.h>

#if _WIN32
#  include <windows.h>
#  include <winsock.h>
#else
#  include <error.h>
#  include <resolv.h>
#  include <sys/socket.h>
#  include <sys/types.h>
#  include <netinet/in.h>
#  include <arpa/inet.h>
#  include <fcntl.h>
#endif

#include "options.h"
#include "debug.h"
#include "x11.h"
#include "parser.h"
#include "client.h"


static int sock; // main communication socket

int net_receive_client_data(ClientNetwork *net)
{
	/* Here, we read a new string at the end of the old.
	   This will make sure that, even if our message got in two or more
	   chunks, it'll be still intact. */
	int len = strlen(net->unprocessed_data);
	int b = recv(net->socket_fd, 
			&net->unprocessed_data[len], 4096 - len, 0);

	if(b == 0) // end-of-communication
		return 0;
	else if(b > 0)
		net->unprocessed_data[len+b] = '\0'; // close the string
		
	return 1;
}


void* net_client_add(void* v_socket)
{
	int socket_fd = (int)(long)v_socket;

	debug("Server", "New client added.");

	// set socket as non-blocking
#if _WIN32
	unsigned long iMode=1;
	ioctlsocket(socket_fd, FIONBIO, &iMode);
#else
	int flags = fcntl(socket_fd, F_GETFL, 0);
	if(fcntl(socket_fd, F_SETFL, flags | O_NONBLOCK) < 0)
	{
		perror("fcntl");
		exit(1);
	}
#endif

	// add the client, and enter the main loop
	client_add(socket_fd);

	// if we get here, it means the client got disconnected
	debug("Server", "Client disconnected.");

	return NULL;
}

// Initialize network and open port.
void net_startup()
{
	static int sock;
	struct sockaddr_in address;
	struct sockaddr_in client_address;
	unsigned int client_address_length;
	pthread_t* thread;

	debug("Server", "Initializing network...");

#if _WIN32
	WORD sockVersion;
	WSADATA wsaData;
	sockVersion = MAKEWORD(1, 1);
	WSAStartup(sockVersion, &wsaData);
#endif

	// create socket
	if((sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP)) == -1)
	{
		perror("socket");
		exit(1);
	}

	// reuse socket
	int tr = 1;
	if(setsockopt(sock, SOL_SOCKET, SO_REUSEADDR, (void*)&tr, 
				sizeof(int)) < 0)
	{
		perror("setsockopt");
		exit(1);
	}

	// choose who the server is going to list to
	address.sin_family = AF_INET;
	address.sin_addr.s_addr = INADDR_ANY;
#if 0 // TODO
	if(opt.listen_to == LOCALHOST) // only localhost
		if(!inet_aton("127.0.0.1", &address.sin_addr))
		{
			fprintf(stderr, "It was not possible to get localhost "
					"address.\n");
			exit(1);
		}
#endif
	address.sin_port = htons(52530);

	// bind socket
	if(bind(sock, (struct sockaddr*)&address, sizeof(address)) < 0)
	{
		perror("bind");
		exit(1);
	}

	// listen on socket
	listen(sock, 5);
	debug("Server", "Network initialized, waiting connections.");
	
	// accept incoming connections
	for(;;)
	{
		client_address_length = sizeof(client_address);
		int socket_fd = accept(sock, (struct sockaddr*)&client_address, 
				&client_address_length);
		thread = malloc(sizeof(pthread_t));
		pthread_create(thread, NULL, net_client_add, 
				(void*)(long)socket_fd);
	}
}


void net_disconnect_client(int socket_fd)
{
	shutdown(socket_fd, 2);
}


void net_quit()
{
	// TODO
	close(sock);
}
