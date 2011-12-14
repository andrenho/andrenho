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


int main()
{
	FILE* f = tx_open_file(NULL);
	preprocess(f);
	fclose(f);
	return EXIT_SUCCESS;
}


void preprocess(FILE* f)
{
	do
	{
		printf("%%line %s %d\n", filename, line);

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
				exit(EXIT_FAILURE);
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
			++line;
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
	char* old_filename = strdup(filename);
	int old_line = line;
	int old_c = c;
	TOKEN old_token = token;
	
	// get new filename
	tx_expect(f, STRING);
	filename = strdup(token.string);
	line = 1;
	tx_expect(f, EOL);

	// read file
	FILE* fd = tx_open_file(filename);
	preprocess(fd);
	fclose(fd);

	// restore current file
	filename = old_filename;
	line = old_line;
	c = old_c;
	token = old_token;
}
