#ifndef OPTIONS_H
#define OPTIONS_H

typedef struct Options {
	enum { PALETTE, ALPHA } graphics;
} Options;

extern Options* options;

#endif
