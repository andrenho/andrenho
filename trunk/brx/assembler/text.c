#include <ctype.h>
#include <stdlib.h>
#include <string.h>

#include "text.h"

int line = 1;
char* filename = "stdin";

static int c=0;
static char string[255];

FILE* tx_open_file(char* filename)
{
	FILE* f = stdin;
	if(filename)
	{
		// TODO - check errors
		f = fopen(filename, "r");
	}
	c = fgetc(f);
	return f;
}


void tx_next_token(FILE* f)
{
	TOKEN_TYPE type;

	// skip spaces
	while (isblank(c))
		c = fgetc(f); 

	// check for token type
	if(c == EOF)
	{
		token = (TOKEN) { _EOF, "" };
		c = fgetc(f); 
		return;
	}
	else if(c == '\n')
	{
		token = (TOKEN) { EOL, "\n" };
		c = fgetc(f); 
		return;
	}
	else if(c == '%')
		type = PREPROCESSOR;
	else if(c == '"')
	{
		int k = 0;
		string[k++] = c = fgetc(f);
		while(c != '"')
		{
			string[k++] = c = fgetc(f);
			if(c == '\n' || c == EOF)
			{
				fprintf(stderr, "Expected: \" in %s:%d.\n",
						filename, line);
				exit(1);
			}
		}
		string[k-1] = 0;
		token.type = STRING;
		strcpy(token.string, string);
		c = fgetc(f);
		return;
	}
	else if(isalpha(c) || c == '.' || c == '$') // TODO
		type = ID;
	else if(c == ';')
	{
		while((c = fgetc(f)) != '\n' && c != EOF);
	}
	else
	{
		fprintf(stderr, "Unexpected char: %c in %s:%d.\n", c,
				filename, line);
		exit(1);
	}

	// construct token
	int k = 0;
	string[k++] = c;
	while(!isblank(c) && c != '\n' && c != EOF && k < 255)
		string[k++] = c = fgetc(f);
	string[k-1] = 0;

	// return structure
	token.type = type;
	strcpy(token.string, string);
}


void tx_expect(FILE* f, TOKEN_TYPE type)
{
	tx_next_token(f);
	if(token.type != type)
	{
		fprintf(stderr, "Invalid token in %s:%d.\n", filename, line);
		exit(1);
	}
}
