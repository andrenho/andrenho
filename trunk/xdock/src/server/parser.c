// TODO - check error messages

#include "parser.h"

#include <ctype.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "debug.h"
#include "client.h"
#include "x11_cmd.h"



inline static int translate_color(char* color)
{
	int n_color;
	// TODO
	n_color = strtol(color, NULL, 10);
	return n_color;
}


inline static int assert_cmd(int value, char* cmd)
{
	if(!value)
		fprintf(stderr, "From client: error executing command %s.\n", cmd);
	return value;
}


inline static int syntax_error(char* cmd)
{
	fprintf(stderr, "Syntax error from client: invalid syntax for "
			"command %s.\n", cmd);
	return 0;
}


static int parse_command(char* command, Client* client)
{
	// remove enter from the end
	char* pos = strchr(command, '\n');
	if(pos)
		pos[0] = '\0';
	debug("Server < Client", "%s", command);

	if(client->net.mode == XPM)
	{
		if(strcmp(command, ".") == 0)
		{
			int n = x11_add_image(&client->wm, 
					client->net.xpm_file.xpm, 0);
			if(!net_send_client_data(&client->net, "OK %d\n", n))
				syntax_error("SEND_XPM"); // TODO
			client->net.mode = COMMAND;
			return 1;
		}
		else
		{
			if(client->net.xpm_file.current_line == 0)
			{
				int x, y, c, s;
				if(sscanf(command, "%d %d %d %d", &x, &y, &c, 
							&s) != 4)
					syntax_error("SEND_XPM");
				client->net.xpm_file.max_lines = 1 + c + y;
				client->net.xpm_file.xpm = malloc(client->net.xpm_file.max_lines);
			}
			if(client->net.xpm_file.current_line == client->net.xpm_file.max_lines)
				syntax_error("SEND_XPM"); // TODO
			client->net.xpm_file.xpm[client->net.xpm_file.current_line++] = strdup(command);
			return 1;
		}
	}

	// get command name
	char cmd[30];
	sscanf(command, "%30s", cmd);

	if(!strcmp(cmd, "PANEL"))
	{
		int x, y, w, h;
		if(sscanf(command, "%s %d %d %d %d", cmd, &x, &y, &w, &h) != 5)
			return syntax_error(cmd);
		return assert_cmd(x11_panel(&client->wm, x, y, w, h), cmd);
	}
	else if(!strcmp(cmd, "PIXEL"))
	{
		char color[25];
		int n_color, x, y;
		if(sscanf(command, "%s %25s %d %d", cmd, color, &x, &y) != 4)
			return syntax_error(cmd);
		n_color = translate_color(color);
		return assert_cmd(x11_pixel(&client->wm, n_color, x, y), cmd);
	}
	else if(!strcmp(cmd, "LINE"))
	{
		char color[25];
		int n_color, x1, x2, y1, y2;
		if(sscanf(command, "%s %25s %d %d %d %d", cmd, color, 
					&x1, &y1, &x2, &y2) != 6)
			return syntax_error(cmd);
		n_color = translate_color(color);
		return assert_cmd(x11_line(&client->wm, n_color, 
					x1, y1, x2, y2), cmd);
	}
	else if(!strcmp(cmd, "RECTANGLE"))
	{
		char color[25];
		int n_color, x, y, w, h;
		if(sscanf(command, "%s %25s %d %d %d %d", cmd, color, 
					&x, &y, &w, &h) != 6)
			return syntax_error(cmd);
		n_color = translate_color(color);
		return assert_cmd(x11_rectangle(&client->wm, n_color, 
					x, y, w, h), cmd);
	}
	else if(!strcmp(cmd, "BOX"))
	{
		char color[25];
		int n_color, x, y, w, h;
		if(sscanf(command, "%s %25s %d %d %d %d", cmd, color, 
					&x, &y, &w, &h) != 6)
			return syntax_error(cmd);
		n_color = translate_color(color);
		return assert_cmd(x11_box(&client->wm, n_color, 
					x, y, w, h), cmd);
	}
	else if(!strcmp(cmd, "UPDATE"))
	{
		x11_update(&client->wm);
		return 1;
	}
	else if(!strcmp(cmd, "MOVEBOX"))
	{
		char bg_color[25];
		int x, y, w, h, move_x, move_y, n_color;
		if(sscanf(command, "%s %d %d %d %d %d %d %s", cmd, &x, &y, 
					&w, &h, &move_x, &move_y, 
					bg_color) != 8)
			return syntax_error(cmd);
		n_color = translate_color(bg_color);
		return assert_cmd(x11_movebox(&client->wm, x, y, w, h,
					move_x, move_y, n_color), cmd);
	}
	else if(!strcmp(cmd, "SEND_XPM"))
	{
		// TODO - themed
		client->net.mode = XPM;
		client->net.xpm_file.current_line = 0;
		return 1;
	}
	else
	{
		fprintf(stderr, "Parse error from client: invalid "
				"command %s.\n", cmd);
		return 0;
	}
}


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
