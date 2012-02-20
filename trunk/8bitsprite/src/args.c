#include "args.h"

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>


static void usage(char* progname, int reason);


/* get and interpret command line arguments*/
OPTIONS* args_get(int argc, char* argv[])
{
	int opt;
	char* size = 0;

	// find parameters
	while((opt = getopt(argc, argv, "")) != -1)
	{
		switch(opt)
		{
		/*
		case 't':
			size = strdup(optarg);
			if(!discover_size(size, &w, &h))
				usage(argv[0], EXIT_FAILURE);
			break;
		*/
		default:
			usage(argv[0], EXIT_FAILURE);
		}
	}
	if(optind >= argc)
		usage(argv[0], EXIT_FAILURE);
	
	// create option struct
	OPTIONS* opts = malloc(sizeof(OPTIONS));
	opts->filename = argv[argc-1];
	FILE *f;
	if((f = fopen(opts->filename, "r")))
	{
		fclose(f);
		opts->file = OPEN;
	}
	else
		opts->file = NEW;
	return opts;
}


static void usage(char* progname, int reason)
{
	printf("8bitsprite is a pixel art editor focused in 8 bit images.\n");
	printf("Usage: %s -t 32x32 filename.8bs (create a new imageset)\n", 
			progname);
	printf("   or: %s filename.8bs (load a imageset)\n", progname);
	exit(reason);
}


/*
static int discover_size(char* size, int* w, int* h)
{
	char c, sz[2][50];
	int i = 0, j = 0, k = 0;

	// boundary check
	if(strlen(size) > 15)
		return 0;

	while((c = size[i++]))
	{
		if(isdigit(c)) // found a number
			sz[j][k++] = c;
		else if(c == 'x' && j == 0) // found the first 'x'
		{
			sz[j][k] = 0; // finish the first number
			++j; k = 0;
		}
		else // something invalid
			return 0;
	}
	sz[j][k] = 0; // finish the second number

	// find out numbers
	*w = strtol(sz[0], (char**)NULL, 10);
	*h = strtol(sz[1], (char**)NULL, 10);

	return 1;
}
*/
