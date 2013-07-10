#include "parser.h"

#include <ctype.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "debug.h"
#include "client.h"
#include "x11_cmd.h"
#include "x11_util.h"


// Returns a error if value is 0. Used to check if a command failed.
inline static int assert_cmd(int value, char* command, Client* c)
{
	if(!value)
		fprintf(stderr, "Error executing command '%s' from client %s.\n", 
				command, c->id);
	return value;
}


// Returns a syntax error.
inline static int syntax_error(Client* c, char* command)
{
	fprintf(stderr, "Syntax error from client %s: invalid syntax for "
			"command '%s'.\n", c->id ? c->id : "unknown", command);
	return 0;
}


// Parse a command sent by the client, and executes it.
static int parse_command(char* command, Client* client)
{
	// remove enter from the end
	char* pos = strchr(command, '\n');
	if(pos)
		pos[0] = '\0';
	debug_comm(client, FROM, "%s", command);

	// ignore comments and white lines
	if(command[0] == '#' || command[0] == '\0')
		return 1;

	// check for authentication
	if(!client->authorized)
	{
		if(strncmp(command, "HELLO", 5) == 0)
		{
			char cmd[30], id[25];
			if(sscanf(command, "%29s %24s", cmd, id) != 2)
				return syntax_error(NULL, cmd);
			strncpy(client->id, id, 25);
			client->authorized = 1;
			return 1;
		}
		else
		{
			fprintf(stderr, "Client didn't say HELLO and was "
					"disconnected.\n");
			return 0;
		}
	}
	
	// check for XPM data
	if(client->mode == XPM)
	{
		if(strcmp(command, ".") == 0)
		{
			if(x11_add_image(client,
					client->xpm_file.name,
					client->xpm_file.xpm) == 0)
			{
				fprintf(stderr, "Client %s sent invalid XPM "
						"image data.\n", client->id);
				free_xpm(client->xpm_file.xpm);
				return 0;
			}
			free_xpm(client->xpm_file.xpm);
			client->mode = COMMAND;
			return 1;
		}
		else
		{
			if(client->xpm_file.current_line == 0)
			{
				int x, y, c, s;
				if(sscanf(command, "%d %d %d %d", &x, &y, &c, 
							&s) != 4)
					syntax_error(client, command);
				client->xpm_file.max_lines = 1 + c + y;
				client->xpm_file.xpm = malloc(client->xpm_file.max_lines * sizeof(char*));
			}
			if(client->xpm_file.current_line == client->xpm_file.max_lines)
			{
				fprintf(stderr, "Client %s sent invalid XPM "
						"image data.\n", client->id);
				free_xpm(client->xpm_file.xpm);
				return 0;
			}
			client->xpm_file.xpm[client->xpm_file.current_line++] = strdup(command);
			return 1;
		}
	}

	// get command name
	char cmd[30];
	sscanf(command, "%29s", cmd);

	if(!strcmp(cmd, "PANEL"))
	{
		int x, y, w, h;
		if(sscanf(command, "%s %d %d %d %d", cmd, &x, &y, &w, &h) != 5)
			return syntax_error(client, command);
		return assert_cmd(x11_panel(client, x, y, w, h), 
				command, client);
	}
	else if(!strcmp(cmd, "PIXEL"))
	{
		char color[25];
		int x, y;
		if(sscanf(command, "%s %24s %d %d", cmd, color, &x, &y) != 4)
			return syntax_error(client, command);
		return assert_cmd(x11_pixel(client, color, x, y), 
				command, client);
	}
	else if(!strcmp(cmd, "LINE"))
	{
		char color[25];
		int x1, x2, y1, y2;
		if(sscanf(command, "%s %24s %d %d %d %d", cmd, color, 
					&x1, &y1, &x2, &y2) != 6)
			return syntax_error(client, command);
		return assert_cmd(x11_line(client, color, 
					x1, y1, x2, y2), command, client);
	}
	else if(!strcmp(cmd, "RECTANGLE"))
	{
		char color[25];
		int x, y, w, h;
		if(sscanf(command, "%s %24s %d %d %d %d", cmd, color, 
					&x, &y, &w, &h) != 6)
			return syntax_error(client, command);
		return assert_cmd(x11_rectangle(client, color, 
					x, y, w, h), command, client);
	}
	else if(!strcmp(cmd, "BOX"))
	{
		char color[25];
		int x, y, w, h;
		if(sscanf(command, "%s %24s %d %d %d %d", cmd, color, 
					&x, &y, &w, &h) != 6)
			return syntax_error(client, command);
		return assert_cmd(x11_box(client, color, 
					x, y, w, h), command, client);
	}
	else if(!strcmp(cmd, "UPDATE"))
	{
		x11_update(client);
		return 1;
	}
	else if(!strcmp(cmd, "MOVEBOX"))
	{
		char bg_color[25];
		int x, y, w, h, move_x, move_y;
		if(sscanf(command, "%s %d %d %d %d %d %d %24s", cmd, &x, &y, 
					&w, &h, &move_x, &move_y, 
					bg_color) != 8)
			return syntax_error(client, command);
		return assert_cmd(x11_movebox(client, x, y, w, h,
					move_x, move_y, bg_color), 
				command, client);
	}
	else if(!strcmp(cmd, "SEND_XPM"))
	{
		char img_name[25];
		if(sscanf(command, "%s %24s", cmd, img_name) != 2)
			return syntax_error(client, command);
		client->mode = XPM;
		client->xpm_file.current_line = 0;
		client->xpm_file.name = strdup(img_name);
		return 1;
	}
	else if(!strcmp(cmd, "DRAW_IMAGE"))
	{
		char img[25];
		int x, y;
		if(sscanf(command, "%s %24s %d %d", cmd, img, &x, &y) != 4)
			return syntax_error(client, command);
		return assert_cmd(x11_draw_image(client, img, x, y), 
				command, client);
	}
	else if(!strcmp(cmd, "WRITE"))
	{
		char font[25];
		unsigned char text[255];
		int x, y;
		if(sscanf(command, "%s %24s %d %d \"%254[^\"]\"", cmd, font, 
					&x, &y, text) != 5)
			return syntax_error(client, command);
		return assert_cmd(x11_print(client, font, x, y, text), 
				command, client);
	}
	else
	{
		fprintf(stderr, "Parse error from client: invalid "
				"command %s.\n", cmd);
		return 0;
	}
}


// Checks the data received from the client, splits it into signle commands,
// and call parse_command on them.
int parse_data(char data[4096], Client* client)
{
	int len = strlen(data);
	char* incomplete = NULL;

	// no data
	if(data[0] == '\0')
		return 1;

	// if the last char is not a enter, then we have a incomplete command
	if(data[len-1] != '\n')
	{
		char* last_n = strrchr(data, '\n');
		if(last_n == NULL) // the whole command is incomplete
			return 1; 
		else
			incomplete = last_n + 1;
	}

	// separe the commands and parse them
	char* cur = data;
	while(strchr(cur, '\n'))
	{
		char* next = strchr(cur, '\n') + 1;
		if(!parse_command(cur, /*next-cur,*/ client))
			return 0;
		cur = next;
	}

	// prepare the unparsed data for the next operation
	if(incomplete)
		strcpy(data, incomplete);
	else
		data[0] = '\0';

	return 1;
}
