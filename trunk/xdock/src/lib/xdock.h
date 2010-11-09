#ifndef XDOCK_H
#define XDOCK_H

//
// STRUCTURES
//

// This is the structure that contains information about the connection
// open with xdockserver. It can be read (it is interesting to always check the
// API version) but should not written.
typedef struct {
	int socket_fd;
	int API_version;
} XD_Connection;

// This structure is used to read any events that the user might have caused.
// Currently, only pointer (mouse) events are supported.
typedef struct {
	enum { MOUSE_UP, MOUSE_DOWN } type; // event type
	int x, y;                           // pointer position
} XD_Event;

//
// CONNECTION FUNCTIONS
//

// Opens a new connection with the server. The parameters are:
//   - argc and argv: the same argc and argv from the main procedure of the
//                    application. The library will check from the parameters
//                    -s and -p (or --server and --port) to know where to
//                    connect to. These parameters are NOT removed from the 
//                    list.
//   - id: the ID of the client application (currently used only in debug 
//         reports).
XD_Connection* xd_connect(int argc, char** argv, char id[25]);

// Disconnects from the server.
void xd_disconnect(XD_Connection *c);


// 
// DRAWING FUNCTIONS
//

// Draw a 3D panel.
void xd_panel(XD_Connection* c, int x, int y, int w, int h);

// Draw a single pixel.
void xd_pixel(XD_Connection* c, char color[25], int x, int y);

// Draw a line.
void xd_line(XD_Connection* c, char color[25], int x1, int y1, int x2, int y2);

// Draw a empty rectangle (only the borders).
void xd_rectangle(XD_Connection* c, char color[25], int x, int y, int w, int h);

// Draw a filled rectangle.
void xd_box(XD_Connection* c, char color[25], int x, int y, int w, int h);

// Any changes made to the dock are only made to a buffer image. This command
// updates the buffer to the screen.
void xd_update(XD_Connection* c);

// Moves a rectangle x and y pixels. This is useful for drawing moving graphics.
void xd_move_box(XD_Connection* c, int x, int y, int w, int h, int move_x,
		int move_y, char bg_color[25]);

// Sends a XPM image to the server, giving it a 'name'.
void xd_send_xpm(XD_Connection* c, char name[25], char** xpm);

// Draw a image that was sent with `xd_send_xpm`.
void xd_draw_image(XD_Connection* c, char image[25], int x, int y);

// Write a text using the given font.
void xd_write(XD_Connection* c, char font[25], int x, int y, char* fmt, ...);

// Check if there is a events, and returns immediately. If there is a event, 1
// is returned and the XD_Event structure is filled. If not, 0 is returned.
int xd_event(XD_Connection* c, XD_Event* e);

// Like `xd_event`, but waits until a event happens and then returns.
void xd_wait_event(XD_Connection* c, XD_Event* e);

#endif
