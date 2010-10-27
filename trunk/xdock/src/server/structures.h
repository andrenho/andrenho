#ifndef STRUCTURES_H
#define STRUCTURES_H

// TODO - document this!!!

#include <X11/Xlib.h>
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


typedef struct {
	char** xpm;
	int current_line;
	int max_lines;
	char* name;
} XPM_File;


struct Color {
	char name[25];
	int pixel;
	UT_hash_handle hh;
};


struct Image {
	char name[25];
	Pixmap pixmap;
	UT_hash_handle hh;
};


struct Font {
	char name[25];
	Pixmap chr[255];
	UT_hash_handle hh;
};


typedef struct {
	Window window;
	GC gc;
	Pixmap pixmap;
	int locked_column;	/* if the window is locked in the right side
				   of the screen, this variable has the number
				   of the column (from right to left) */
	struct Color* colors;
	struct Image* images;
	struct Font* fonts;
} WM;


typedef struct {
	int socket_fd;
	int authorized;
	char unprocessed_data[4096];
	char id[25];

	XPM_File xpm_file;
	enum { COMMAND=0, XPM } mode;
} ClientNetwork;


typedef struct Client {
	ClientNetwork net;
	WM wm;
	struct Client* next;
} Client;


#endif
