#ifndef OPTIONS_H
#define OPTIONS_H

#include "uthash.h"

struct ThemeColor {
	char name[25];
	char color[20];
	UT_hash_handle hh;
};

typedef struct {
	enum { NO_VIEW, X11 } toolkit;
	enum { EVERYONE, LOCALHOST } listen_to;
	int debug;
	long dock_color;
	char* theme;
	struct ThemeColor* colors;
	int attract;
	int server_port;
} Options;

extern Options opt;

void opt_parse(int argc, char* argv[]);

#endif
