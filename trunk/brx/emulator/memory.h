#ifndef MEMORY_H
#define MEMORY_H

#include <stdint.h>

typedef struct {
	int size;
	unsigned char* data;
} Memory;

Memory* memory_init(int size_kb);
void memory_step(Memory* memory);
void memory_load(Memory* memory, char* filename, unsigned long pos);
inline uint8_t get(Memory* memory, uint32_t pos);
inline void set(Memory* memory, uint32_t pos, uint8_t data);

#endif
