#ifndef MEMORY_H
#define MEMORY_H

typedef struct {
	int size_kb;
	unsigned char* data;
} Memory;

Memory* memory_init(int size_kb);
void memory_step(Memory* memory);
void memory_load(Memory* memory, char* filename, unsigned long pos);

#endif
