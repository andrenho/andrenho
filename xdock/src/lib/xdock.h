#ifndef XDOCK_H
#define XDOCK_H

typedef struct {
	int socket_fd;
	int API_version;
} XD_Connection;

XD_Connection* xd_connect(int argc, char** argv, char id[25]);
void xd_disconnect(XD_Connection *c);

void xd_panel(XD_Connection* c, int x, int y, int w, int h);
void xd_pixel(XD_Connection* c, char color[25], int x, int y);
void xd_line(XD_Connection* c, char color[25], int x1, int y1, int x2, int y2);
void xd_rectangle(XD_Connection* c, char color[25], int x, int y, int w, int h);
void xd_box(XD_Connection* c, char color[25], int x, int y, int w, int h);
void xd_update(XD_Connection* c);

void xd_move_box(XD_Connection* c, int x, int y, int w, int h, int move_x,
		int move_y, char bg_color[25]);
void xd_send_xpm(XD_Connection* c, char name[25], char** xpm);
void xd_draw_image(XD_Connection* c, char image[25], int x, int y);
void xd_write(XD_Connection* c, char font[25], int x, int y, char text[255]);

#endif
