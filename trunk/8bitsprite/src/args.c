#include "args.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>


static void usage(int reason)
{
	printf("Usage\n");
	exit(reason);
}


OPTIONS* args_get(int argc, char* argv[])
{
	int opt;
	char* size;

	while((opt = getopt(argc, argv, "t:")) != -1)
	{
		switch(opt)
		{
		case 't':
			size = strdup(optarg);
			break;
		default:
			usage(EXIT_FAILURE);
		}
	}
	
	if(optind >= argc)
		usage(EXIT_FAILURE);
	
	

	return NULL;
}
