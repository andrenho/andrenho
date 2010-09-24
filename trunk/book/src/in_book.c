#include "in_book.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void book_input(Book* book, FILE* f)
{
	int c;
	int pos = 0;
	int sz = 1024;
	book->text = malloc(sz);
	book->text[0] = 0;

	book->metadata.title = NULL;
	book->metadata.author = NULL;
	book->metadata.language = NULL;
	
	book->format = NULL;

	while((c = fgetc(f)) != EOF)
	{
		book->text[pos] = c;
		book->text[pos+1] = 0;
		pos++;

		if(pos+1 > sz)
		{
			sz += 1024;
			book->text = realloc(book->text, sz);
		}
	}
}
