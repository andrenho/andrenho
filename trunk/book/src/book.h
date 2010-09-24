#ifndef BOOK_H
#define BOOK_H

#include <stdbool.h>

typedef struct {
	char* title;
	char* author;
	char* language;
} BookMetadata;

typedef struct {
	int pos;
	enum { CHAPTER, B_ON, B_OFF, I_ON, I_OFF, U_ON, U_OFF, } type;
	union {
		char* name;
		bool has_number;
	} chapter;
} FormatMarker;

typedef struct {
	BookMetadata metadata;
	char *text;
	FormatMarker* format;
} Book;

#endif
