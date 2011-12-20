#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "text.h"
#include "../uthash/uthash.h"

struct my_defines {
	char name[255];
	char value[255];
	UT_hash_handle hh;
};
static struct my_defines *defines = NULL;

FILE* f = NULL;
static long address = 0x0;

static void dline();
static void define();
static void opcode();
static void data();
static void invalid_opcode_format();
static void byte(unsigned char b);
static void word(unsigned long w);
static unsigned long parse_number();
static unsigned char find_register(char* s);

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
			else if(strcmp(token.string, "org") == 0)
			{
				tx_next_token(f);
				address = strtoul(token.string, NULL, 16);
				tx_expect(f, EOL);
				printf("{0x%lX} ", address);
			}
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

	printf("[%s:%d] ", filename, line);
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
		byte(opcodes[opc_idx].d << 1);
		parse_number();
		return;
	}

	// format J
	if(token.type == ID || token.type == NUMBER)
	{
		unsigned long x = (opcodes[opc_idx].j << 25);
		x |= (parse_number() - address);
		word(x);
	}
	else if(token.type == REGISTER)
	{
		unsigned char r1 = find_register(token.string);
		tx_expect(f, COMMA);
		tx_expect(f, REGISTER); // second register
		unsigned char r2 = find_register(token.string);
		tx_expect(f, COMMA);
		tx_next_token(f);
		// format R
		if(token.type == REGISTER)
		{
			unsigned char r3 = find_register(token.string);
			unsigned long x = (opcodes[opc_idx].i << 9);
			x |= (r1 << 6);
			x |= (r2 << 3);
			x |= r3;
			byte((x << 8) & 0xff);
			byte(x & 0xff);
		}
		// format I
		else if(token.type == ID || token.type == NUMBER)
		{
			unsigned long x = (opcodes[opc_idx].i << 25);
			x |= (r1 << 22);
			x |= (r2 << 19);
			unsigned long n = parse_number();
			if(n > 0x2ffff)
			{
				fprintf(stderr, "Number 0x%lx too high in %s:%d.\n",
						n, filename, line);
				exit(1);
			}
			x |= parse_number();
			word(x);
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
			int i = 1;
			do { byte(token.string[i++]); } while(token.string[i+1]);
			for(i=(strlen(token.string) % sz); i>0; i--)
				byte(0x0);
		}
		else if(token.type == NUMBER)
		{
			unsigned long ul = strtoul(token.string, NULL, 16);
			int i;
			for(i=((sz-1)*8); i>=0; i-=8)
				byte((ul >> i) & 0xff);
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


static unsigned long parse_number()
{
	if(token.type == ID)
	{
		struct my_defines *d = NULL;
		HASH_FIND_STR(defines, token.string, d);
		if(d)
			strcpy(token.string, d->value);
		else
		{
			fprintf(stderr, "Invalid token %s in %s:%d.", token.string, filename, line);
			exit(1);
		}
	}
	
	unsigned long i = 0;
	// hexa
	if(token.string[0] == '0' && token.string[1] == 'x')
		i = strtoul(token.string, NULL, 16);
	// binary
	else if(token.string[strlen(token.string)] == 'b')
		i = strtoul(token.string, NULL, 2);
	// decimal
	else
		i = strtoul(token.string, NULL, 10);

	return i;
}


static void invalid_opcode_format()
{
	fprintf(stderr, "Invalid opcode format in %s:%d.\n", filename, line);
	exit(EXIT_FAILURE);
}


static void byte(unsigned char b)
{
	address++;
	printf("0x%02X ", b);
}


static void word(unsigned long w)
{
	byte((w >> 24) & 0xff);
	byte((w >> 16) & 0xff);
	byte((w >> 8) & 0xff);
	byte(w & 0xff);
}


static unsigned char find_register(char* s)
{
	int i = 0;
	while(registers[i].name)
	{
		if(strcmp(registers[i].name, s) == 0)
			return registers[i].code;
		i++;
	}
	fprintf(stderr, "Invalid register %s in %s:%d.", s, filename, line);
	exit(1);
}
