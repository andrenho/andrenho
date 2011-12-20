#ifndef TEXT_H
#define TEXT_H

#include <stdio.h>
#include "opcodes.h"

typedef enum { 
	NOTYPE = 0, PREPROCESSOR, STRING, ID, SECTION, REGISTER, NUMBER, COMMA, 
	LABEL, OPCODE, EOL, _EOF, COMMENT, INITIALIZED_DATA, SBRACKET, CBRACKET,
	VERTICALBAR
} TOKEN_TYPE;
typedef struct {
	TOKEN_TYPE type;
	char string[255];
} TOKEN;
TOKEN token;

extern int line;
extern char* filename;
extern int c;

FILE* tx_open_file(char* filename);
void tx_next_token(FILE* f);
void tx_expect(FILE* f, TOKEN_TYPE type);

#endif
