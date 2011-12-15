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
static void invalid_opcode_format();

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
	char* opcode = strdup(token.string);

	tx_next_token(f);
	
	// format D
	if(token.type == EOL)
	{
		
	}

	// format J
	if(token.type == ID || token.type == NUMBER)
	{
		
	}
	else if(token.type == REGISTER)
	{
		tx_expect(f, COMMA);
		tx_expect(f, REGISTER); // second register
		tx_expect(f, COMMA);
		tx_next_token(f);
		// format R
		if(token.type == REGISTER)
			;
		// format I
		else if(token.type == ID || token.type == NUMBER)
			;
		else
			invalid_opcode_format();
	}
	else
		invalid_opcode_format();

	// nothing after
	tx_next_token(f);
	if(token.type != EOL)
		invalid_opcode_format();

	free(opcode);
}


static void invalid_opcode_format()
{
	fprintf(stderr, "Invalid opcode format in %s:%d.\n", filename, line);
	exit(EXIT_FAILURE);
}
