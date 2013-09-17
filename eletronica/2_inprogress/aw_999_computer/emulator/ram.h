#ifndef RAM_H
#define RAM_H

#include <stdint.h>

void ram_init();
uint8_t ram_get(uint32_t pos);
void ram_set(uint32_t pos, uint8_t data);

#endif
