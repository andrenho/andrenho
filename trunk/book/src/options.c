#include "options.h"

#include <stdlib.h>
#include <stdio.h>

Options* parse_options(int argc, char** argv)
{
	(void) argc;
	(void) argv;

	Options* opt = malloc(sizeof(Options));
	opt->input_format = BOOK;
	opt->output_format = BOOK;
	opt->input_file = stdin;
	opt->output_file = stdout;

	return opt;
}
