#include "editor.h"

#include "util.h"

static Image* image;
static int zoom = 16;
static int ed_w;

static void draw();
static void input();

void editor_run(Image* img)
{
	image = img;
	ed_w = screen->w - (img->sf->w * 2 + 20);
	if(ed_w > (screen->w - 100))
		ed_w = screen->w - 100;

	int done_editing = 0;
	while(!done_editing)
	{
		draw();
		input();
	}
}


static void draw()
{
	SDL_FillRect(screen, NULL, BLACK);

	int ix = 0, iy = 0, x = 0, y = 0;
	while(iy < image->sf->h && y < screen->h)
	{
		// pixel
		SDL_Rect r = { x, y, zoom, zoom };
		SDL_FillRect(screen, &r, P(image->sf,ix,iy));

		// grid
		if(zoom >= 12)
		{
			int i;
			for(i=0; i<zoom; i++)
			{
				P(screen, x+zoom-1, y+i) = i%2 ? WHITE : BLACK;
				P(screen, x+i, y+zoom-1) = i%2 ? WHITE : BLACK;
			}
		}

		++ix;
		x += zoom;

		if(ix >= image->sf->w || x >= ed_w)
		{
			ix = x = 0;
			++iy;
			y += zoom;
		}
	}

	// draw image
	print(ed_w + 10, 10, "Image");
	SDL_Rect r = { ed_w+10, 40 };
	SDL_BlitSurface(image->sf, NULL, screen, &r);

	// draw image (2x)
	print(ed_w + 10, 50 + r.y, "Image (2x)");
	for(x=0; x<image->sf->w; x++)
		for(y=0; y<image->sf->h; y++)
		{
			P(screen,(ed_w+10+(x*2)),(120+(y*2))) = P(image->sf,x,y);
			P(screen,(ed_w+10+(x*2)),(121+(y*2))) = P(image->sf,x,y);
			P(screen,(ed_w+11+(x*2)),(120+(y*2))) = P(image->sf,x,y);
			P(screen,(ed_w+11+(x*2)),(121+(y*2))) = P(image->sf,x,y);
		}

	SDL_Flip(screen);
}


static void input()
{
	
}
