#ifndef OPCODES_H
#define OPCODES_H

typedef struct {
	char* name;
	unsigned char d, r, i, j;
} OPCODES;
typedef struct {
	char* name;
	unsigned char code;
} REGISTERS;

extern OPCODES opcodes[];
extern REGISTERS registers[];

#endif
