#include <stdio.h>
#include <stdlib.h>

#include "options.h"
#include "book.h"
#include "in_book.h"
#include "out_book.h"

int main(int argc, char** argv)
{
	Book book;
	Options* opt = parse_options(argc, argv);

	switch(opt->input_format)
	{
		case BOOK:
			book_input(&book, opt->input_file);
			break;
		default:
			abort();
	}

	switch(opt->output_format)
	{
		case BOOK:
			book_output(&book, opt->output_file);
			break;
		default:
			abort();
	}

	return 0;
}
