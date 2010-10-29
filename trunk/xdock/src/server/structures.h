/* This file contains all structures used by xdockserver. */

#ifndef STRUCTURES_H
#define STRUCTURES_H

#include <X11/Xlib.h>
#include "uthash.h"	// Hash macro library, from <http://uthash.sf.net/>.

// Strucutre used to store the colors of the theme.
struct ThemeColor {
	char name[25];		// Name of the theme color (such as 'lit, 
				// 'unlit', etc)
	char color[20];		// Color used
	UT_hash_handle hh;
};


// Set of user changeable options.
typedef struct {
	enum { X11 } toolkit;	// Toolkit used (not implemented)
	int debug;		// Show debug information
	long dock_color;	// Color of the dock
	char* theme;		// Theme used
	struct ThemeColor* colors;	// set of colors in the theme
	int attract;		// Attraction to the right border, in pixels
	int server_port;	// Port the server will listen to
	enum { EVERYONE, LOCALHOST } listen_to; // Addresses the server will
						// listen to
} Options;


// Structure used to store XPM files.
typedef struct {
	char** xpm;
	int current_line;
	int max_lines;
	char* name;
} XPM_File;


// Color used by the client.
struct Color {
	char name[25];
	int pixel;
	UT_hash_handle hh;
};


// Images uploaded by the client.
struct Image {
	char name[25];
	Pixmap pixmap;
	UT_hash_handle hh;
};


// Fonts usable for the client.
struct Font {
	char name[25];
	Pixmap chr[255];
	UT_hash_handle hh;
};


// Linked list of the clients.
typedef struct Client {
	/*
	 * Client information
	 */
	char id[25];		// Client identification (set by himself)

	/*
	 * Window Manager information
	 */
	Window window;		// X11 window
	GC gc;
	Pixmap pixmap;		// backstore pixmap; all operations happen in
				// this pixmap and are transfered to the window
				// with a UPDATE command

	struct Color* colors;	// hash of colors
	struct Image* images;	// hash of images uploaded
	struct Font* fonts;	// hash of fonts

	int locked_column;	// if the window is locked in the right side
				// of the screen, this variable has the number
				// of the column (from right to left)

	/* 
	 * Network information
	 */
	int socket_fd;			// socket number
	int authorized;			// if the client idenfied himself
	char unprocessed_data[4096];	// data received by the server, but that
					// wasn't still processed

	/*
	 * Parser information
	 */
	XPM_File xpm_file;		// when a XPM is being uploaded, it is
					// store here temporarily
	enum { COMMAND=0, XPM } mode;	// what is being interpreted: commands
					// or a XPM file

	struct Client* next;		// next client in this linked list
} Client;


#endif
