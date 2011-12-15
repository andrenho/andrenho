#include <stdio.h>
#include <stdlib.h>
#include "text.h"
#include "../uthash/uthash.h"

#define MEM_INCREMENT 10000

struct my_labels {
	char name[255];
	long address;
	UT_hash_handle hh;
};
static struct my_labels *labels = NULL;

static FILE* f = NULL;
static long address = 0x0;
static char* code;
static long code_sz = MEM_INCREMENT;

static void label();
static void opcode();
static void data();
static void invalid_opcode_format();
static void print_labels();
static void print_code();
static void add_to_code();


int main()
{
	filename = NULL;
	line = 0;
	code = malloc(MEM_INCREMENT);
	code[0] = 0;

	f = tx_open_file(NULL);

	do
	{
		// find next token
		tx_next_token(f);

		// filename / line
		if(token.type == PREPROCESSOR)
		{
			// get filename
			add_to_code();
			tx_next_token(f);
			if(filename)
				free(filename);
			filename = strdup(token.string);
			
			// get line number
			add_to_code();
			tx_next_token(f);
			line = strtoul(token.string, NULL, 16);

			add_to_code();
			tx_expect(f, EOL);
			add_to_code();
		}

		// label
		else if(token.type == LABEL)
			label();

		// org
		else if(token.type == ID && strcmp(token.string, "org") == 0)
		{
			tx_next_token(f);
			address = strtoul(token.string, NULL, 16);
			tx_expect(f, EOL);
		}

		// opcode
		else if(token.type == OPCODE)
			opcode();

		else if(token.type == INITIALIZED_DATA)
			data();

		// others
		else
			add_to_code();
	
	} while(token.type != _EOF);

	print_labels();
	print_code();

	fclose(f);
	return EXIT_SUCCESS;
}


static void label()
{
	token.string[strlen(token.string)-1] = 0;
		
	// TODO - check label redefinition

	struct my_labels *d;
	d = malloc(sizeof(struct my_labels));
	strcpy(d->name, token.string);
	d->address = address;
	HASH_ADD_STR(labels, name, d);
}


static void opcode()
{
	printf("1. %s\n", token.string);
	add_to_code();
	tx_next_token(f);

	// format D
	if(token.type == EOL)
	{
		add_to_code();
		address += 1;
	}

	// format J
	if(token.type == ID || token.type == NUMBER)
	{
		add_to_code();
		address += 4;
	}
	else if(token.type == REGISTER)
	{
		add_to_code();
		tx_expect(f, COMMA);
		add_to_code();
		tx_expect(f, REGISTER); // second register
		add_to_code();
		tx_expect(f, COMMA);
		add_to_code();
		tx_next_token(f);
		add_to_code();
		// format R
		if(token.type == REGISTER)
			address += 2;
		// format I
		else if(token.type == ID || token.type == NUMBER)
			address += 4;
		else
			invalid_opcode_format();
	}
	else
		invalid_opcode_format();

	printf("2. %s\n", token.string);

	// nothing after
	tx_next_token(f);
	printf("3. %s\n", token.string);
	add_to_code();
	if(token.type != EOL)
		invalid_opcode_format();
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
	add_to_code();

	do
	{
		tx_next_token(f);
		
		if(token.type == STRING)
			address += strlen(token.string);
		else if(token.type == NUMBER)
			address += sz;
		else
		{
			fprintf(stderr, "Invalid value for data: %s in %s:%d.\n", 
					token.string, filename, line);
			exit(EXIT_FAILURE);
		}
		add_to_code();

		tx_next_token(f);
		add_to_code();
		if(token.type != EOL && token.type != COMMA)
		{
			fprintf(stderr, "Syntax error in %s:%d: %s.\n", 
					filename, line, token.string);
			exit(EXIT_FAILURE);
		}

	} while(token.type != EOL);

	tx_next_token(f);
}


static void print_labels()
{
	struct my_labels *lb, *tmp;
	HASH_ITER(hh, labels, lb, tmp)
		printf("%%define %s %ld\n", lb->name, lb->address);
}


static void print_code()
{
	printf("%s", code);
}


static void invalid_opcode_format()
{
	fprintf(stderr, "Invalid opcode format in %s:%d.\n", filename, line);
	exit(EXIT_FAILURE);
}

static void add_to_code()
{
	if(strlen(token.string) + strlen(code) > code_sz)
	{
		code_sz += MEM_INCREMENT;
		code = realloc(code, code_sz);
	}
	strcat(code, token.string);
	strcat(code, " ");
}
