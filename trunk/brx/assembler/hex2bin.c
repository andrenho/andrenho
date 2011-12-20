#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "text.h"

FILE* f;
unsigned long address = 0x0;

void args(int argc, char* argv[], char** bin_file, char** debug_file);

int main(int argc, char* argv[])
{
	int old_line = -1;

	// get argument names
	char *bin_file[255], *debug_file[255];
	args(argc, argv, bin_file, debug_file);

	// open files
	FILE *bin, *debug;
	bin = fopen(*bin_file, "w");
	if(*debug_file)
		debug = fopen(*debug_file, "w");
	if(!bin || (*debug_file && !debug))
	{
		fprintf(stderr, "One of the files could not be open.\n");
		exit(1);
	}

	// intialize variables
	f = tx_open_file(NULL);
	filename = NULL;
	line = 1;

	do
	{
		// find next token
		tx_next_token(f);

		// line
		if(token.type == SBRACKET)
		{
			tx_next_token(f); // filename
			if(filename)
				free(filename);
			filename = strdup(token.string);
			tx_expect(f, COLON);
			tx_next_token(f); // line
			line = strtoul(token.string, NULL, 16);
			tx_expect(f, SBRACKET);
		}

		// address
		else if(token.type == CBRACKET)
		{
			tx_next_token(f);
			address = strtoul(token.string, NULL, 16);
			tx_expect(f, CBRACKET);
		}

		// opcode
		else if(token.type == NUMBER)
		{
			if(*debug_file && old_line != line)
			{
				fprintf(debug, "%s %d %ld\n", filename, line, address);
				old_line = line;
			}
			unsigned char c = strtoul(token.string, NULL, 16);
			fprintf(bin, "%c", c);
			address++;
		}

		// invalid token
		else if(token.type != _EOF)
		{
			fprintf(stderr, "Invalid token %s.\n", token.string);
			exit(1);
		}
		
	} while(token.type != _EOF);

	// close files
	fclose(f);
	fclose(bin);
	if(*debug_file)
		fclose(debug);

	return EXIT_SUCCESS;
}


void args(int argc, char* argv[], char** bin_file, char** debug_file)
{
	if(argc < 2 || argc > 3)
	{
		fprintf(stderr, "Usage: hex2bin bin_filename [debug_filename]\n");
		exit(1);
	}

	*bin_file = argv[1];
	if(argc == 3)
		*debug_file = argv[2];
	else
		*debug_file = NULL;
}
