#include "memory.h"

#include <stdlib.h>
#include <stdio.h>

#include "curses_.h"

Memory* memory_init(int size_kb)
{
	Memory* memory = malloc(sizeof(Memory));
	memory->size_kb = size_kb * 1024;
	memory->data = malloc(memory->size_kb);
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
		if(pos >= memory->size_kb)
		{
			curses_end();
			fprintf(stderr, "BIOS size exceeds memory size.\n");
			exit(1);
		}
		memory->data[pos++] = (unsigned char)c;
	}
}
