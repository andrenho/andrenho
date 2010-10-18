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


static int parse_command(char* command, int len)
{
	char* cmd = strdup(command);
	cmd[len-1] = '\0'; // we replace '\n' here
	if(cmd[len-2] == '\r')
		cmd[len-2] = '\0';
	int pos = 0;
	
	// read command
	char* nx = expect_id(cmd);
	if(nx == NULL)
		return 0;

	// parse command
	if(strcmp(cmd, "PANEL"))
	{
		// do something
	}
	else
		return 0;

	free(cmd);
	return 1;
}


int parse_data(char data[4096], CommandQueue** queue)
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
			return; 
		else
			incomplete = last_n + 1;
	}

	// separe the commands and parse them
	char* cur = data;
	while(strchr(cur, '\n'))
	{
		char* next = strchr(cur, '\n') + 1;
		if(!parse_command(cur, next-cur))
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
