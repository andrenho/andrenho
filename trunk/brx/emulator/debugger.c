#include "debugger.h"
#include "../uthash/uthash.h"

#include <stdlib.h>
#include <stdio.h>
#include <sys/stat.h>
#include <curses.h>

typedef struct {
	unsigned long address;
	char filename[255];
	int line;
	UT_hash_handle hh;
} DEBUG_INFO;
static DEBUG_INFO* debug_info = NULL;

typedef struct {
	char filename[255];
	char* source;
	int size;
	UT_hash_handle hh;
} SOURCE;
static SOURCE* source = NULL;

// prototypes
static void read_file(SOURCE *src);
static void print_source(SOURCE *src, int line);

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

	// store information
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
	fclose(f);

	// read files
	DEBUG_INFO *di, *tmp;
	HASH_ITER(hh, debug_info, di, tmp)
	{
		SOURCE* src = NULL;
		HASH_FIND_STR(source, di->filename, src);
		if(!src) // if source wasn't read yet
		{
			src = malloc(sizeof(SOURCE));
			strcpy(src->filename, di->filename);
			read_file(src);
			HASH_ADD_STR(source, filename, src);
		}
	}       
}


void debugger_run(Debugger* debugger)
{
	timeout(-1);

	// find out file and line
	DEBUG_INFO *di;
	HASH_FIND_INT(debug_info, &debugger->cpu->p, di);

	if(di)
	{
		// print file on screen, marking the current line
		SOURCE *src;
		HASH_FIND_STR(source, di->filename, src);
		if(src)
			print_source(src, di->line);
		else
			mvaddstr(0, 0, "Source file could not be open.");
	}
	else
		// print empty string
		mvaddstr(0, 0, "Debugging information not found.");

	// wait for input
	refresh();

	timeout(-1);
}


static void read_file(SOURCE *src)
{
	src->source = NULL;
	src->size = 0;
	
	FILE* f = fopen(src->filename, "r");

	if(f)
	{	struct stat st;
		fstat(fileno(f), &st);
		src->size = st.st_size;
		src->source = malloc(st.st_size);
		int i = 0;
		while(!feof(f))
		{
			src->source[i++] = fgetc(f);
			if(i >= st.st_size)
				abort();
		}
	}

	getch();
}


static void print_source(SOURCE *src, int line)
{
	clear();
	move(0, 0);
	int i=0;

	// print source
	while(i < src->size)
	{
		int c = src->source[i++];
		addch(c);
	}

	// invert current line
	mvchgat(line-1, 0, COLS, A_REVERSE, 0, NULL);
}
