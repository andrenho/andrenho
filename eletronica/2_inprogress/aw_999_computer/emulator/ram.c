#include "ram.h"

#include <stdlib.h>
#include <stdio.h>

#include "display.h"
extern Display* display;

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

	if(pos >= 0x100 && pos <= 0x2ff) { // video
		if(data[0x2ff] == 0) { // terminal
			display_send_command(display, (char*)&data[0x100]);
		} else { // pixel
			if(pos < 0x2f8) {
				int vpos = ((pos - 0x100) * 8);
				uint8_t v = d;
				for(int i=7; i>=0; i--) {
					display->data[vpos+i] = (v & 1);
					v >>= 1;
				}
			}
		}
	}
}


void ram_load_rom(uint32_t pos, char* filename)
{
	FILE* f = fopen(filename, "r");
	if(!f) {
		fprintf(stderr, "Could not open file %s.\n", filename);
		exit(1);
	}

	while(!feof(f)) {
		ram_set(pos++, (uint8_t)fgetc(f));
	}

	fclose(f);
}
