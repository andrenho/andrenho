#include <stdio.h>
#include <stdlib.h>
#include "text.h"
#include "../uthash/uthash.h"

struct my_defines {
	char name[255];
	char value[255];
	UT_hash_handle hh;
};
static struct my_defines *defines = NULL;

FILE* f = NULL;

static void dline();
static void define();
static void opcode();
static void data();
static void invalid_opcode_format();
static void byte(unsigned char b);

int main()
{
	f = tx_open_file(NULL);
	filename = NULL;
	line = 1;

	do
	{
		// find next token
		tx_next_token(f);

		// directives
		if(token.type == PREPROCESSOR)
		{
			if(strcmp(token.string, "%line") == 0)
				dline();
			else if(strcmp(token.string, "%define") == 0)
				define();
			else
			{
				fprintf(stderr, "Invalid preprocessor %s in %s:%d.\n", 
						token.string, filename, line);
				exit(EXIT_FAILURE);
			}
		}

		// opcode
		else if(token.type == OPCODE)
			opcode();

		// initialized data (db and friends)
		else if(token.type == INITIALIZED_DATA)
			data();

		// other directives
		else if(token.type == ID)
		{
			if(strcmp(token.string, "section") == 0) // TODO
				tx_next_token(f);
		}

		// semantic error
		else if(token.type != EOL && token.type != _EOF)
		{
			fprintf(stderr, "Unexpected token %s in %s:%d.\n",
					token.string, filename, line);
			exit(EXIT_FAILURE);
		}

	} while(token.type != _EOF);

	fclose(f);
	return EXIT_SUCCESS;
}


static void dline()
{
	tx_next_token(f);
	if(filename)
		free(filename);
	filename = strdup(token.string);
			
	// get line number
	tx_next_token(f);
	line = strtoul(token.string, NULL, 16);

	tx_expect(f, EOL);
}


static void define()
{
	struct my_defines *def = malloc(sizeof(struct my_defines));

	tx_next_token(f);
	
	strcpy(def->name, token.string);
	tx_next_token(f);
	strcpy(def->value, token.string);
	tx_expect(f, EOL);

	HASH_ADD_STR(defines, name, def);
}


static void opcode()
{
	char* opc = strdup(token.string);
	int k = 0;

	// find opcode index
	int opc_idx = -1;
	for(k=0; opcodes[k].name; k++)
		if(strcmp(opc, opcodes[k].name) == 0)
		{
			opc_idx = k;
			break;;
		}
	if(opc_idx == -1)
	{
		fprintf(stderr, "Invalid opcode %s in %s:%d.\n", opc, filename, line);
		exit(EXIT_FAILURE);
	}

	// next token
	tx_next_token(f);
	
	// format D
	if(token.type == EOL)
	{
		byte(opcodes[opc_idx].d);
		return;
	}

	// format J
	if(token.type == ID || token.type == NUMBER)
	{
		// TODO
	}
	else if(token.type == REGISTER)
	{
		tx_expect(f, COMMA);
		tx_expect(f, REGISTER); // second register
		tx_expect(f, COMMA);
		tx_next_token(f);
		// format R
		if(token.type == REGISTER)
		{
			// TODO
		}
		// format I
		else if(token.type == ID || token.type == NUMBER)
		{
			// TODO
		}
		else
			invalid_opcode_format();
	}
	else
		invalid_opcode_format();

	// nothing after
	tx_next_token(f);
	if(token.type != EOL)
		invalid_opcode_format();

	free(opc);
}


static void data()
{
	int sz;
	switch(token.string[1])
	{
		case 'b': sz = 1; break;
		case 'w': sz = 2; break;
		case 'd': sz = 4; break;
		case 'q': sz = 8; break;
		default: abort();
	}

	do
	{
		tx_next_token(f);
		
		if(token.type == STRING)
		{
			// TODO
		}
		else if(token.type == NUMBER)
		{
			// TODO
		}
		else
		{
			fprintf(stderr, "Invalid value for data: %s in %s:%d.\n", 
					token.string, filename, line);
			exit(EXIT_FAILURE);
		}

		tx_next_token(f);
		if(token.type != EOL && token.type != COMMA)
		{
			fprintf(stderr, "Syntax error in %s:%d: %s.\n", 
					filename, line, token.string);
			exit(EXIT_FAILURE);
		}

	} while(token.type != EOL);
}


static void invalid_opcode_format()
{
	fprintf(stderr, "Invalid opcode format in %s:%d.\n", filename, line);
	exit(EXIT_FAILURE);
}


int i = 0;
static void byte(unsigned char b)
{
	printf("%02X ", b);
	if(i++ % 16 == 0)
		printf("\n");
}
