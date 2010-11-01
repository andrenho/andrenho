#include "network.h"

#ifdef WIN32
#	include <winsock.h>
#else
#	include <sys/socket.h>
#	include <sys/un.h>
#	include <netinet/in.h>
#	include <netdb.h>
#	include <fcntl.h>
#	define INVALID_SOCKET -1
#	define SOCKET_ERROR -1
#endif
#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>
#include <errno.h>

int net_connect(char* host, int port)
{
	struct hostent* hostInfo;
	long hostAddress;
	struct sockaddr_in address;

#ifdef WIN32
	WORD wVersionRequested;
	WSADATA wsaData;
	wVersionRequested = MAKEWORD(1, 1);
	if(WSAStartup(wVersionRequested, &wsaData) != 0)
	{
		fprintf(stderr, "Could not open winsock.\n");
		return -1;
	}
#endif

	int sock = socket(PF_INET, SOCK_STREAM, 0);
	if(sock == SOCKET_ERROR)
	{
		fprintf(stderr, "Could not make a socket.\n");
		return -1;
	}

	hostInfo = gethostbyname(host);
	if(!hostInfo)
	{
		fprintf(stderr, "Couldn't find host %s.\n", host);
		return -1;
	}

	memcpy(&hostAddress, hostInfo->h_addr, hostInfo->h_length);

	address.sin_addr.s_addr = hostAddress;
	address.sin_port = htons(port);
	address.sin_family = AF_INET;
	memset(address.sin_zero, '\0', sizeof(address.sin_zero));

	if(connect(sock, (struct sockaddr*)&address, sizeof(address)) == SOCKET_ERROR)
	{
		fprintf(stderr, "Could not connect to applet server. Check if the applet server is running.\n");
		return -1;
	}
	else
	{
		// set socket as nonblocking
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
	}

	return sock;
}

int net_send(int sock, char* fmt, ...)
{
	char buf[4096];
	va_list ap;

	// parse and print message
	va_start(ap, fmt);
	int bytes = vsnprintf(buf, 4096, fmt, ap);
	va_end(ap);

	int sent, n = 0;
again:
	sent = send(sock, &buf[n], bytes - n, 0);
	if(sent == -1)
	{
		goto again;
		buf[bytes-1] = '\0';
		fprintf(stderr, "Error sending message '%s'.\n", buf);
		perror("send");
		return 0;
	}
	else if(sent + n < bytes)
	{
		n += sent;
		goto again;
	}
	else
		return 1;
}

int net_recv(int sock, char msg[255])
{
	/*
	unsigned char* c = malloc(length);
	int i = recv(sock, c, length, 0);
	if(i == -1)
	{
		free(c);;
		return NULL;
	}
	else if(i == 0)
	{
		fprintf(stderr, "Connection lost.\n");
		exit(1);
	}
	else
		return c;
	*/
	return 1;
}

void net_disconnect(int sock)
{
#ifdef WIN32
	closesocket(sock);
#else
	if(close(sock) == SOCKET_ERROR)
		fprintf(stderr, "Could not close socket\n");
#endif
}
