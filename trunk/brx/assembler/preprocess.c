#include <stdio.h>
#include <string.h>
#include "text.h"
#include "../uthash/uthash.h"

static void preprocess(FILE* f);
static void define(FILE* f);
static void replace_token_define();
static void include(FILE* f);

struct my_defines {
	char name[255];
	char value[255];
	UT_hash_handle hh;
};
static struct my_defines *defines = NULL;

typedef struct my_filestack {
	char *filename;
	int line;
	struct my_filestack *next;
} my_filestack;
static my_filestack *filestack = NULL;


int main()
{
	FILE* f = tx_open_file(NULL);
	preprocess(f);
	fclose(f);
	return 0;
}


void preprocess(FILE* f)
{
	do
	{
		// find next token
		tx_next_token(f);

		// preprocessor reserved words
		if(token.type == PREPROCESSOR)
		{
			if(strcmp(token.string, "\%define") == 0)
				define(f);
			else if(strcmp(token.string, "\%include") == 0)
				include(f);
			else
			{
				fprintf(stderr, "Unsupported directive %s in %s:%d.\n", 
						token.string, filename, line);
				exit(1);
			}
		}
		// not preprocessor reserved words
		else 
		{
			printf("%s ", token.string);
			while(token.type != EOL && token.type != _EOF)
			{
				tx_next_token(f);
				replace_token_define();
				printf("%s ", token.string);
			}
		}
	} while(token.type != _EOF);
}


static void define(FILE* f)
{
	struct my_defines *d;
	d = malloc(sizeof(struct my_defines));

	// read from file
	tx_expect(f, ID);
	strcpy(d->name, token.string);
	tx_next_token(f);
	strcpy(d->value, token.string);
	tx_expect(f, EOL);

	// add to hash
	HASH_ADD_STR(defines, name, d);
}


static void replace_token_define()
{
	struct my_defines *d = NULL;
	HASH_FIND_STR(defines, token.string, d);
	if(d)
		strcpy(token.string, d->value);
}


static void include(FILE* f)
{
	my_filestack *fs = malloc(sizeof(my_filestack));
	fs->filename = strdup(filename);
	fs->line = line;
	LL_PREPEND(filestack, fs); // TODO

	tx_expect(f, STRING);
	char* file = strdup(token.string);
	tx_expect(f, EOL);
	
	
}
