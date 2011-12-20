#include "debugger.h"
#include "../uthash/uthash.h"

#include <stdlib.h>
#include <stdio.h>

typedef struct {
	unsigned long address;
	char filename[255];
	int line;
	UT_hash_handle hh;
} DEBUG_INFO;
DEBUG_INFO* debug_info = NULL;


Debugger* debugger_init(CPU* cpu, Memory *mem)
{
	Debugger* debugger = malloc(sizeof(Debugger));
	debugger->cpu = cpu;
	debugger->mem = mem;
	return debugger;
}


void debugger_load(Debugger* debugger, char* filename)
{
	FILE* f = fopen(filename, "r");
	if(!f)
		return;

	while(!feof(f))
	{
		char filename[255];
		int line;
		unsigned long address;
		fscanf(f, "%s %d %ld", filename, &line, &address);
		
		DEBUG_INFO* di = malloc(sizeof(DEBUG_INFO));
		strcpy(di->filename, filename);
		di->line = line;
		di->address = address;
		HASH_ADD_INT(debug_info, address, di);
	}
}


void debugger_run(Debugger* debugger)
{
	(void)debugger;

	// find out file and line

}
