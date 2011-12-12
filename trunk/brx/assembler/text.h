#ifndef TEXT_H
#define TEXT_H

#include <stdio.h>

typedef enum { PREPROCESSOR, STRING, ID, EOL, _EOF } TOKEN_TYPE;
typedef struct {
	TOKEN_TYPE type;
	char string[255];
} TOKEN;
TOKEN token;

extern int line;
extern char* filename;

FILE* tx_open_file(char* filename);
void tx_next_token(FILE* f);
void tx_expect(FILE* f, TOKEN_TYPE type);

#endif
