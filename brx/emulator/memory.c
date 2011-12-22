#include "memory.h"

#include <stdlib.h>
#include <stdio.h>

#include "curses_.h"

Memory* memory_init(int size_kb)
{
	Memory* memory = malloc(sizeof(Memory));
	memory->size = size_kb * 1024;
	memory->data = malloc(memory->size);
	return memory;
}


void memory_step(Memory* memory)
{
	(void) memory;
}


void memory_load(Memory* memory, char* filename, unsigned long pos)
{
	FILE* f = fopen(filename, "r");
	if(!f)
	{
		curses_end();
		fprintf(stderr, "Could not open file %s.\n", filename);
		exit(1);
	}

	int c;
	while((c = fgetc(f)) != EOF)
	{
		if(pos >= memory->size)
		{
			curses_end();
			fprintf(stderr, "BIOS size exceeds memory size.\n");
			exit(1);
		}
		memory->data[pos++] = (unsigned char)c;
	}
}


inline uint8_t get(Memory* memory, uint32_t pos)
{
	if(pos > memory->size)
	{
		fprintf(stderr, "Invalid memory position 0x%X.\n", pos);
		exit(1);
	}
	return memory->data[pos];
}


inline void set(Memory* memory, uint32_t pos, uint8_t data)
{
	if(pos > memory->size)
	{
		fprintf(stderr, "Invalid memory position 0x%X.\n", pos);
		exit(1);
	}
	memory->data[pos] = data;
}
