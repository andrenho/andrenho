#include "network.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include <unistd.h>
#include <errno.h>

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


static int net_receive_client_data(Client* c);

static int sock; // main communication socket

// Initialize network and open port.
void net_startup()
{
	struct sockaddr_in address;

	debug("Initializing network...");

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

	// mark socket as non-blocking
#if _WIN32
	unsigned long iMode=1;
	ioctlsocket(sock, FIONBIO, &iMode);
#else
	int flags = fcntl(sock, F_GETFL, 0);
	if(fcntl(sock, F_SETFL, flags | O_NONBLOCK) < 0)
	{
		perror("fcntl");
		exit(1);
	}
#endif

	// choose who the server is going to list to
	address.sin_family = AF_INET;
	address.sin_addr.s_addr = INADDR_ANY;
#if !_WIN32 // TODO
	if(opt.listen_to == LOCALHOST) // only localhost
		if(!inet_aton("127.0.0.1", &address.sin_addr))
		{
			fprintf(stderr, "It was not possible to get localhost "
					"address.\n");
			exit(1);
		}
#endif
	address.sin_port = htons(opt.server_port);

	// bind socket
	if(bind(sock, (struct sockaddr*)&address, sizeof(address)) < 0)
	{
		perror("bind");
		exit(1);
	}

	// listen on socket
	listen(sock, 5);
	debug("Network initialized, waiting connections.");
}


void net_check_for_clients()
{
	struct sockaddr_in client_address;
	unsigned int client_address_length;

	// accept incoming connections
	client_address_length = sizeof(client_address);
	int socket_fd = accept(sock, (struct sockaddr*)&client_address, 
			&client_address_length);

	
	if(socket_fd >= 0) // a new client connected
	{
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
		Client* client = client_add();
		client->socket_fd = socket_fd;
		client->authorized = 0;
		client->unprocessed_data[0] = '\0';
		client->mode = COMMAND;

		net_send_client_data(client, "XDOCK %d\n", API_VERSION);
	}
}


void net_receive_data()
{
	Client* c = clients;
	while(c)
	{
		if(net_receive_client_data(c) == 0)
		{
			// client disconnected
			client_destroy(c);
			break;
		}
		else if(parse_data(c->unprocessed_data, c) == 0)
		{
			// syntax error, disconnect client
			client_destroy(c);
			break;
		}
		c = c->next;
	}
}


static int net_receive_client_data(Client* c)
{
	/* Here, we read a new string at the end of the old.
	   This will make sure that, even if our message got in two or more
	   chunks, it'll be still intact. */
	int len = strlen(c->unprocessed_data);
	int b = recv(c->socket_fd, 
			&c->unprocessed_data[len], 4096 - len, 0);

	if(b == 0) // end-of-communication
		return 0;
	else if(b > 0)
		c->unprocessed_data[len+b] = '\0'; // close the string
		
	return 1;
}


int net_send_client_data(Client* c, char* fmt, ...)
{
	// TODO - timeout???
	
	va_list ap;
	char buffer[2048];

	// parse and message
	va_start(ap, fmt);
	int n = vsnprintf(buffer, 2048, fmt, ap);
	va_end(ap);

	// send data
	int pos = 0;
	while((pos += send(c->socket_fd, &buffer[pos], n - pos, 0)) < n);

	debug_comm(c, TO, "%s", buffer);

	return 1;
}


void net_disconnect_client(int socket_fd)
{
	debug("Client disconnected.");
	shutdown(socket_fd, 2);
}


void net_quit()
{
	// TODO
	close(sock);
}
