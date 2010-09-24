#ifndef OPTIONS_H
#define OPTIONS_H

#include <stdio.h>

typedef enum { BOOK } Format;

typedef struct {
	Format input_format;
	Format output_format;
	FILE* input_file;
	FILE* output_file;
} Options;

Options* parse_options(int argc, char** argv);

#endif
