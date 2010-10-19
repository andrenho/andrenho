#ifndef OPTIONS_H
#define OPTIONS_H

typedef struct {
	enum { NO_VIEW, X11 } toolkit;
	enum { EVERYONE, LOCALHOST } listen_to;
	int debug;
	long dock_color;
} Options;

extern Options opt;

void opt_parse(int argc, char* argv[]);

#endif
