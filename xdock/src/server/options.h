#ifndef OPTIONS_H
#define OPTIONS_H

typedef struct {
	char *panel_bg,
	     *panel_lt,
	     *panel_sw,
	     *unlit,
	     *lit,
	     *bright,
	     *glow,
	     *warning;
} Theme;

typedef struct {
	enum { NO_VIEW, X11 } toolkit;
	enum { EVERYONE, LOCALHOST } listen_to;
	int debug;
	long dock_color;
	char* theme;
	int attract;
} Options;

extern Options opt;
extern Theme theme;

void opt_parse(int argc, char* argv[]);

#endif
