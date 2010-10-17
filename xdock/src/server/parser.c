#include "parser.h"

#include <stdlib.h>

#include "debug.h"

// client messages

// server messages

char* bytes_left[4096];
int n_bytes_left = 0;


static int split_commands(char* input, int bytes, char* commands[])
{
}


// Parse input received from the client.
void parse_input(Client* client, char* input, int bytes)
{
	int i;
	char* commands[200];

	int n_commands = split_commands(input, bytes, commands);
	for(i=0; i<n_commands; i++)
	{
		debug("Client", "%s", commands[i]);
	}
}
