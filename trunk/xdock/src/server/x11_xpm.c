#include <X11/Xlib.h>

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

static char * blarg_xpm[] = {
"16 7 2 1",
"* c #000000",
". c #ffffff",
"**..*...........",
"*.*.*...........",
"**..*..**.**..**",
"*.*.*.*.*.*..*.*",
"**..*..**.*...**",
"...............*",
".............**."
};

#define MAX(x,y) ((x) > (y) ? (x) : (y))
#define MIN(x,y) ((x) < (y) ? (x) : (y))
#define CH1(n) ('.' + (n % ('`'-'.')))
#define CH2(n) ('.' + (n / ('`'-'.')))

char** square_xpm(long color)
{
	int ln = 0;
	int r = (color & 0xff0000) >> 16,
	    g = (color & 0xff00) >> 8,
	    b = (color & 0xff);
	int cr = r+46, cg = g+46, cb = b+46;

	char** sq = malloc(sizeof(char*) * (1 + 93 + 96));
	
	// values
	sq[ln++] = strdup("96 96 93 2");

	// colors
	sq[ln++] = strdup("``\tc #ffffff");
	int i;
	for(i=0; i<92; i++)
	{
		sq[ln] = malloc(13);
		sprintf(sq[ln++], "%c%c\tc #%02X%02X%02X", CH1(i), CH2(i),
				MIN(MAX(cr, 0), 255),
				MIN(MAX(cg, 0), 255),
				MIN(MAX(cb, 0), 255));
		cr--; cg--; cb--;
	}

	int x, y;
	for(y=0; y<=1; y++)
	{
		sq[ln] = malloc((96 * 2) + 1);
		for(x=0; x<=96; x++)
			sq[ln][x] = sq[ln][x+1] = '`';
		sq[ln][(96 * 2)] = '\0';
		ln++;
	}

	for(y=2; y<94; y++)
	{
		int color = (y - 2) / 2;
		sq[ln] = malloc((96 * 2) + 1);
		strcpy(sq[ln], "````");
		strcpy(&sq[ln][94*2], "````\0");
		for(x=2; x<94; x+=2)
		{
			sq[ln][x*2] = sq[ln][x*2+2] = CH1(color);
			sq[ln][x*2+1] = sq[ln][x*2+3] = CH2(color);
			color++;
		}
		ln++;
	}

	for(y=94; y<=95; y++)
	{
		sq[ln] = malloc((96 * 2) + 1);
		for(x=0; x<=96; x++)
			sq[ln][x] = sq[ln][x+1] = '`';
		sq[ln][(96 * 2)] = '\0';
		ln++;
	}

	for(i=0; i<(1 + 93 + 96); i++)
		printf("%s\n", sq[i]);

	return sq;
}


Pixmap xpm_to_pixmap(char* xpm[], Display* display, Window window)
{
	Colormap colormap = DefaultColormap(display, DefaultScreen(display));

	// <values>
	char* values = strdup(xpm[0]);
	char *ws = strtok(values, " \t"), *hs = strtok(NULL, " \t"),
	     *sncol = strtok(NULL, " \t"), *sszcol = strtok(NULL, " \t");
	int w = strtol(ws, NULL, 10), h = strtol(hs, NULL, 10), 
	    ncol = strtol(sncol, NULL, 10), szcol = strtol(sszcol, NULL, 10);
	free(values);

	// create pixmap
	int tmp, depth;
	Window tmpw;
	XGetGeometry(display, window, &tmpw, &tmp, &tmp, &tmp, &tmp, &tmp, 
			&depth);
	Pixmap pixmap = XCreatePixmap(display, window, w, h, depth);
	GC gc = XCreateGC(display, pixmap,
			0,        // mask of values
			NULL );   // array of values

	// colors
	struct color {
		char* str;
		int x_color;
	} * color = malloc(sizeof(struct color) * ncol);
	int i;
	for(i=0; i<ncol; i++)
	{
		XColor xcolor;
		char *chr = malloc(szcol + 1);
		strncpy(chr, xpm[i+1], szcol);
		chr[szcol] = '\0';
		char* cl = strdup(&xpm[i+1][szcol+1]);
		char *type = strtok(cl, " \t"), 
		     *cl_value = strtok(NULL, " \t");
		(void) type;
		XParseColor(display, colormap, cl_value, &xcolor);
		color[i].str = strdup(chr);
		XAllocColor(display, colormap, &xcolor);
		color[i].x_color = xcolor.pixel;
		free(cl);
	}

	// pixels
	int x, y;
	for(y=0; y<h; y++)
		for(x=0; x<w; x++)
		{
			for(i=0; i<ncol; i++)
			{
				char* ch = &xpm[1+ncol+y][x*szcol];
				if(strncmp(color[i].str, ch, szcol) == 0)
				{
					XSetForeground(display, gc,
							color[i].x_color);
					XDrawPoint(display, pixmap, gc, x, y);
					break;
				}
			}
		}

	// free everything
	for(i=0; i<ncol; i++)
		free(color[i].str);
	free(color);

	return pixmap;
}


typedef struct {
	Window window;
	GC gc;
} WM;

static Display* display;
static int white, black;
static int screen_w, screen_h;

int main()
{
	WM* wm = malloc(sizeof(WM));
	
	//
	// initialize X11
	//
	XInitThreads();

	display = XOpenDisplay(NULL);
	if(!display)
	{
		fprintf(stderr, "Could not open display.\n");
		return 0;
	}

	white = WhitePixel(display, DefaultScreen(display));
	black = BlackPixel(display, DefaultScreen(display));

	screen_w = XDisplayWidth(display, DefaultScreen(display));
	screen_h = XDisplayHeight(display, DefaultScreen(display));

	//
	// setup client
	//

	XEvent evt;

	// create window
	wm->window = XCreateSimpleWindow(display,
			DefaultRootWindow(display),
			0, 0,     // origin
			96, 96,   // size
			0, white, // border
			white);   // backgd

	XSelectInput(display, wm->window, StructureNotifyMask);
	XMapWindow(display, wm->window);

	do 
		XNextEvent(display, &evt);
	while(evt.type != MapNotify);

	// select input
	XSelectInput(display, wm->window, 
			  ExposureMask 
			| StructureNotifyMask);

	// create GC
	wm->gc = XCreateGC(display, wm->window,
			0,        // mask of values
			NULL );   // array of values

	Pixmap pixmap = xpm_to_pixmap(square_xpm(0x808080), display, wm->window);
	XCopyArea(display, pixmap, wm->window, wm->gc,
			0, 0, 96, 96, 0, 0);

	while(1)
	{
		XNextEvent(display, &evt);
		switch(evt.type)
		{
			case Expose:
				break;
		}
	}

	for(;;);

	return 0;

}
