#ifndef OPCODES_H
#define OPCODES_H

typedef struct {
	char* name;
	unsigned char d, r, i, j;
} OPCODES;

extern OPCODES opcodes[];

#endif
