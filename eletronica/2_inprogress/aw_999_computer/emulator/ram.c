#include "ram.h"

#include <stdlib.h>
#include <stdio.h>

uint8_t data[512*1024];

void ram_init()
{
}


uint8_t ram_get(uint32_t pos)
{
	if(pos >= 512*1024) {
		fprintf(stderr, "Invalid memory position %X.\n", pos);
		exit(-1);
	}
	return data[pos];
}


void ram_set(uint32_t pos, uint8_t d)
{
	if(pos >= 512*1024) {
		fprintf(stderr, "Invalid memory position %X.\n", pos);
		exit(-1);
	}


	data[pos] = d;
}
