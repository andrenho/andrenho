#include "xdock.h"

#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "network.h"

#ifdef _WIN32
#  include <signal.h>

XD_Connection* connections[255];
int n_connections = 0;

static void quit(int sig)
{
	int i;
	for(i=0; i<n_connections; i++)
		xd_disconnect(connections[i]);
	exit(0);
}
#endif

XD_Connection* xd_connect(int argc, char** argv, char id[25])
{
	int i;
	char* server = "localhost";
	int port = 52530;

	// parse arguments
	for(i=1; i<argc; i++)
	{
		if(!strcmp(argv[i], "-s") || !strcmp(argv[i], "--server"))
		{
			if(i+1 < argc)
				server = argv[i+1];
			else
			{
				fprintf(stderr, "Invalid server address.\n");
				exit(EXIT_FAILURE);
			}
		}
		else if(!strcmp(argv[i], "-p") || !strcmp(argv[i], "--port"))
		{
			if(i+1 < argc)
				port = (int)strtol(argv[i+1], NULL, 10);
			if(i+1 >= argc || port == 0)
			{
				fprintf(stderr, "Invalid port.\n");
				exit(EXIT_FAILURE);
			}
		}
	}
	
	// open connection
	int sock = net_connect(server, port);
	if(sock != -1)
	{
		XD_Connection *cn = malloc(sizeof(XD_Connection));
		cn->socket_fd = sock;

		// receive hello
		char msg[4096], cmd[25];
		int api_version;
		while(!net_recv(sock, msg));
		int n = sscanf(msg, "%24s %d", cmd, &api_version);
		if(n != 2 || strcmp(cmd, "XDOCK") != 0)
		{
			fprintf(stderr, "Invalid identification from server. "
					"Received: '%s'\n", msg);
			return NULL;
		}
		else
			cn->API_version = api_version;

		// send hello
		if(!net_send(sock, "HELLO %s\n", id))
			return NULL;
#ifdef _WIN32
		signal(SIGINT, quit);
		connections[n_connections++] = cn;
#endif	
		return cn;
	}
	else
		return NULL;
}


void xd_disconnect(XD_Connection *c)
{
	assert(c);
	net_disconnect(c->socket_fd);
}


void xd_panel(XD_Connection* c, int x, int y, int w, int h)
{
	assert(c);
	net_send(c->socket_fd, "PANEL %d %d %d %d\n", x, y, w, h);
}


void xd_pixel(XD_Connection* c, char color[25], int x, int y) 
{
	assert(c);
	net_send(c->socket_fd, "PIXEL %s %d %d\n", color, x, y);
}


void xd_line(XD_Connection* c, char color[25], int x1, int y1, int x2, int y2) 
{
	assert(c);
	net_send(c->socket_fd, "LINE %s %d %d %d %d\n", color, x1, y1, x2, y2);
}


void xd_rectangle(XD_Connection* c, char color[25], int x, int y, int w, int h) 
{ 
	assert(c);
	net_send(c->socket_fd, "RECTANGLE %s %d %d %d %d\n", color, x, y, w, h);
}


void xd_box(XD_Connection* c, char color[25], int x, int y, int w, int h)
{
	assert(c);
	net_send(c->socket_fd, "BOX %s %d %d %d %d\n", color, x, y, w, h);
}


void xd_update(XD_Connection* c)
{
	assert(c);
	net_send(c->socket_fd, "UPDATE\n");
}

void xd_move_box(XD_Connection* c, int x, int y, int w, int h, int move_x,
		int move_y, char bg_color[25])
{
	assert(c);
	net_send(c->socket_fd, "MOVEBOX %d %d %d %d %d %d %s\n", x, y, w, h,
			move_x, move_y, bg_color);
}

void xd_send_xpm(XD_Connection* c, char name[25], char** xpm)
{
	assert(c);
	int i, w, h, ncols, szcol;
	net_send(c->socket_fd, "SEND_XPM %s\n", name);
	sscanf(xpm[0], "%d %d %d %d", &w, &h, &ncols, &szcol);
	for(i=0; i<(1+ncols+h); i++)
		net_send(c->socket_fd, "%s\n", xpm[i]);
	net_send(c->socket_fd, ".\n");
}

void xd_draw_image(XD_Connection* c, char image[25], int x, int y)
{
	assert(c);
	net_send(c->socket_fd, "DRAW_IMAGE %s %d %d\n", image, x, y);
}


void xd_write(XD_Connection* c, char font[25], int x, int y, char text[255])
{
	assert(c);
	net_send(c->socket_fd, "WRITE %s %d %d \"%s\"\n", font, x, y, text);
}


static int invalid_message(char* msg)
{
	fprintf(stderr, "Invalid message from the server: %s.\n", msg);
	return 0;
}


int xd_event(XD_Connection* c, XD_Event* e)
{
	char msg[4096];
	if(net_recv(c->socket_fd, msg))
	{
		char cmd[25], type[25];
		int x, y;
		sscanf(msg, "%24s", cmd);
		if(!strcmp(cmd, "EVENT"))
		{
			int n = sscanf(msg, "%24s %24s %d %d", cmd, type, &x, &y);
			if(n != 4)
				return invalid_message(msg);
			if(!strcmp(type, "up"))
				e->type = MOUSE_UP;
			else if(!strcmp(type, "down"))
				e->type = MOUSE_DOWN;
			else
				return invalid_message(msg);
			e->x = x;
			e->y = y;
			return 1;
		}
		else
			return invalid_message(msg);
	}
	else
		return 0;
}
