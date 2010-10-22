#include "parser.h"

#include <ctype.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "debug.h"
#include "client.h"


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
		x11_panel(&client->wm, x, y, w, h);
		return 1;
	}
	else if(!strcmp(cmd, "UPDATE"))
	{
		x11_update(&client->wm);
		return 1;
	}
	else
	{
		fprintf(stderr, "Parse error from client: invalid command %s.",
				cmd);
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
