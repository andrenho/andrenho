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
	else if(!strcmp(cmd, "UPDATE"))
	{
		x11_update(&client->wm);
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
