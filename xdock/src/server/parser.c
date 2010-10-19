#include "parser.h"

#include <ctype.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "debug.h"
#include "client.h"


static char* next(char* command)
{
	while(command[0] == ' ') // ignore spaces before
		command++;

	while(command[0] != ' ' && command[0] != 0)
		command++;
	command[0] = '\0';
	return ++command;
}


static char* expect_id(char* command)
{
	int i;
	char* nx = next(command);
	for(i=0; command[i] != 0; i++)
		if(!isupper(command[i]))
			return NULL;
	return nx;
}


static char* expect_number(char* command, long* data)
{
	int i;
	char* nx = next(command);
	for(i=0; command[i] != 0; i++)
		if(!isdigit(command[i]))
			return NULL;
	*data = strtol(command, NULL, 10);
	return nx;
}


static int parse_command(char* command, int len, Client* client)
{
	char *cmd = strdup(command);
	char *store_cmd = cmd;
	cmd[len-1] = '\0'; // we replace '\n' here
	if(cmd[len-2] == '\r')
		cmd[len-2] = '\0';

	debug("Server < Client", "%s", cmd);
	
	// read command
	char* nx = expect_id(cmd);
	if(nx == NULL)
		return 0;

	// parse command
	if(strcmp(cmd, "PANEL") == 0)
	{
		long x1, x2, y1, y2;
		if((nx = expect_number(nx, (long*)&x1)) == NULL) 
			return 0;
		if((nx = expect_number(nx, (long*)&x2)) == NULL) 
			return 0;
		if((nx = expect_number(nx, (long*)&y1)) == NULL) 
			return 0;
		if((nx = expect_number(nx, (long*)&y2)) == NULL) 
			return 0;
		if(!x11_draw_panel(client, x1, x2, y1, y2))
			return 0;
	}
	else
		return 0;

	free(store_cmd);
	return 1;
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
		if(!parse_command(cur, next-cur, client))
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
