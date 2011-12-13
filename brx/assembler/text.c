#include <ctype.h>
#include <stdlib.h>
#include <string.h>

#include "text.h"

int line = 1;
char* filename = "stdin";

int c=0;
static char string[255];

static void parse_number();

FILE* tx_open_file(char* filename)
{
	FILE* f = stdin;
	if(filename)
	{
		f = fopen(filename, "r");
		if(!f)
		{
			fprintf(stderr, "Could not open file %s.\n", filename);
			exit(EXIT_FAILURE);
		}
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
		++line;
		token = (TOKEN) { EOL, "\n" };
		c = fgetc(f); 
		return;
	}
	else if(c == ',')
	{
		token = (TOKEN) { COMMA, "," };
		c = fgetc(f); 
		return;
	}
	else if(c == '%')
		type = PREPROCESSOR;
	else if(c == '.')
		type = SECTION;
	else if(c == '$')
		type = REGISTER;
	else if(isdigit(c))
		type = NUMBER;
	else if(isalpha(c))
		type = ID;
	else if(c == ';') // ignore comments
		while((c = fgetc(f)) != '\n' && c != EOF);
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
				exit(EXIT_FAILURE);
			}
		}
		string[k-1] = 0;
		token.type = STRING;
		strcpy(token.string, string);
		c = fgetc(f);
		return;
	}
	else
	{
		fprintf(stderr, "Unexpected char: %c in %s:%d.\n", c,
				filename, line);
		exit(EXIT_FAILURE);
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

	// number? then parse
	if(type == NUMBER)
		parse_number();

	// check if it's a label
	else if(type == ID && token.string[strlen(token.string)-1] == ':')
		type = LABEL;

	// check if it's a opcode
	else if(type == ID)
	{
		int i;
		while(opcodes[i].name)
			if(strcmp(opcodes[i].name, token.string))
			{
				type = OPCODE;
				break;
			}
	}
}


void tx_expect(FILE* f, TOKEN_TYPE type)
{
	tx_next_token(f);
	if(token.type != type)
	{
		fprintf(stderr, "Invalid token in %s:%d.\n", filename, line);
		exit(EXIT_FAILURE);
	}
}


static void parse_number()
{
	unsigned int i = 0;
	// hexa
	if(token.string[0] == '0' && token.string[1] == 'x')
		i = strtoul(token.string, NULL, 16);
	// binary
	else if(token.string[strlen(token.string)] == 'b')
		i = strtoul(token.string, NULL, 2);
	// decimal
	else
		i = strtoul(token.string, NULL, 10);

	sprintf(token.string, "0x%x", i);
}
