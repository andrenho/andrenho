#include <X11/Xlib.h>
#include <X11/Xatom.h>

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define MAX(x,y) ((x) > (y) ? (x) : (y))
#define MIN(x,y) ((x) < (y) ? (x) : (y))
#define CH1(n) ('.' + ((n) % ('`'-'.')))
#define CH2(n) ('.' + ((n) / ('`'-'.')))

// TODO - check for errors
char** square_xpm(long color)
{
	int ln = 0;
	int r = (color & 0xff0000) >> 16,
	    g = (color & 0xff00) >> 8,
	    b = (color & 0xff);
	int cr = r+46, cg = g+46, cb = b+46;

	char** sq = malloc(sizeof(char*) * (1 + 1 + 92 + 49 + 49 + 1 + 96));
	
	// values
	sq[ln++] = strdup("96 96 192 2");

	// inner square colors
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

	// outer square color
	cr = r+100; cg = g+100; cb = b+100;
	for(i=0; i<49; i++)
	{
		sq[ln] = malloc(13);
		sprintf(sq[ln++], "%c%c\tc #%02X%02X%02X", CH1(i+92), CH2(i+92),
				MIN(MAX(cr, 0), 255),
				MIN(MAX(cg, 0), 255),
				MIN(MAX(cb, 0), 255));
		cr--; cg--; cb--;
	}
	cr = r-45; cg = g-45; cb = b-45;
	for(i=0; i<49; i++)
	{
		sq[ln] = malloc(13);
		sprintf(sq[ln++], "%c%c\tc #%02X%02X%02X", CH1(i+140), CH2(i+140),
				MIN(MAX(cr, 0), 255),
				MIN(MAX(cg, 0), 255),
				MIN(MAX(cb, 0), 255));
		cr--; cg--; cb--;
	}
	sq[ln++] = strdup("xx\tc #000000");

	// upper border
	int x, y;
	for(y=0; y<=1; y++)
	{
		sq[ln] = malloc((96 * 2) + 1);
		for(x=0; x<94; x+=2)
		{
			sq[ln][x*2] = sq[ln][x*2+2] = CH1(((x/2)+y) + 92);
			sq[ln][x*2+1] = sq[ln][x*2+3] = CH2(((x/2)+y) + 92);
		}
		if(y == 0)
		{
			sq[ln][188] = CH1(46);
			sq[ln][189] = CH2(46);
		}
		else
		{
			sq[ln][188] = CH1(141);
			sq[ln][189] = CH2(141);
		}
		sq[ln][190] = sq[ln][191] = 'x';
		sq[ln][192] = '\0';
		ln++;
	}

	// middle of the square
	for(y=2; y<94; y++)
	{
		int color = (y - 2) / 2;
		sq[ln] = malloc((96 * 2) + 1);

		sq[ln][0] = CH1(color+92);
		sq[ln][1] = CH2(color+92);
		sq[ln][2] = CH1(color+93);
		sq[ln][3] = CH2(color+93);

		for(x=2; x<94; x+=2)
		{
			sq[ln][x*2] = sq[ln][x*2+2] = CH1(color);
			sq[ln][x*2+1] = sq[ln][x*2+3] = CH2(color);
			color++;
		}

		sq[ln][188] = CH1(((y - 2) / 2)+141);
		sq[ln][189] = CH2(((y - 2) / 2)+141);
		sq[ln][190] = sq[ln][191] = 'x';
		sq[ln][192] = '\0';

		ln++;
	}

	// lower border
	sq[ln] = malloc((96 * 2) + 1);
	sq[ln][0]  = CH1(46);
	sq[ln][1] = CH2(46);
	for(x=1; x<96; x++)
	{
		sq[ln][x*2]  = CH1(((x/2)+(y-94)) + 141);
		sq[ln][x*2+1] = CH2(((x/2)+(y-94)) + 141);
	}
	sq[ln][190] = sq[ln][191] = 'x';
	sq[ln][192] = '\0';
	ln++;

	sq[ln] = malloc((96 * 2) + 1);
	for(x=0; x<(96*2); x++)
		sq[ln][x] = 'x';
	ln++;

	return sq;
}


void free_xpm(char** xpm)
{
	(void) xpm;
	// TODO
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
	int tmp;
	unsigned int depth, utmp;
	Window tmpw;
	XGetGeometry(display, window, &tmpw, &tmp, &tmp, &utmp, &utmp, &utmp, 
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
