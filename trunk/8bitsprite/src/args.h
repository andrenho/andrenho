#ifndef ARGS_H
#define ARGS_H

typedef struct {
	enum { NEW, OPEN } file;
	char* name;
	int x, y;
} OPTIONS;

OPTIONS* args_get(int argc, char* argv[]);

#endif
