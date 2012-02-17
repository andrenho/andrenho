#include "editor.h"

#include "util.h"

static Image* image;
static int zoom = 16;
static int ed_w;
static int selected_color = 0;
static int cursor_x=0, cursor_y=0, cursor_active=1;
static int color_pos[256];

static void draw();
static void draw_editor();
static void draw_miniatures();
static void draw_colors();
static void draw_color(int y, int pos, int color);

static int input();
static void click(int b, int x, int y);
static void key_press(SDL_KeyboardEvent k);
static void change_color(int n);


void editor_run(Image* img)
{
	image = img;
	ed_w = screen->w - (img->sf->w * 2 + 50);
	if(ed_w > (screen->w - 150))
		ed_w = screen->w - 150;

	int done_editing = 0;
	while(!done_editing)
	{
		done_editing = input();
		draw();
		SDL_Delay(1);
	}
}


static void draw()
{
	SDL_FillRect(screen, NULL, BLACK);

	draw_editor();
	draw_miniatures();
	draw_colors();

	SDL_Flip(screen);
}


static void draw_editor()
{
	SDL_FillRect(screen, NULL, BLACK);

	int ix = 0, iy = 0, x = 0, y = 0;
	while(iy < image->sf->h && y < screen->h)
	{
		// pixel
		SDL_Rect r = { x, y, zoom, zoom };
		SDL_FillRect(screen, &r, P(image->sf,ix,iy));
		if(P(image->sf,ix,iy) == BLACK)
			P(screen, x+(zoom/2), y+(zoom/2)) = WHITE;

		// draw cursor
		if(cursor_x == ix && cursor_y == iy && cursor_active &&
				(SDL_GetTicks() / 500) % 2)
		{
			if(P(image->sf,ix,iy) == TRANSPARENT)
				SDL_FillRect(screen, &r, BLACK);
			else
				SDL_FillRect(screen, &r, TRANSPARENT);
		}


		// grid
		if(zoom >= 12)
		{
			int i;
			for(i=0; i<zoom; i++)
			{
				Uint8 c = (i % 2) ? GRAY : BLACK;
				P(screen, x+zoom-1, y+i) = c;
				P(screen, x+i, y+zoom-1) = c;
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
}


static void draw_miniatures()
{
	int x, y;

	// draw image
	print(ed_w + 10, 10, "Image");
	SDL_Rect r = { ed_w+10, 40 };
	SDL_BlitSurface(image->sf, NULL, screen, &r);

	// draw image (2x)
	print(ed_w + 10, 50 + r.y, "Image (2x)");
	for(x=0; x<image->sf->w; x++)
		for(y=0; y<image->sf->h; y++)
		{
			Uint8 c = P(image->sf,x,y);
			if(c != TRANSPARENT)
			{
				P(screen,(ed_w+10+(x*2)),(120+(y*2))) = c;
				P(screen,(ed_w+10+(x*2)),(121+(y*2))) = c;
				P(screen,(ed_w+11+(x*2)),(120+(y*2))) = c;
				P(screen,(ed_w+11+(x*2)),(121+(y*2))) = c;
			}
		}
}


static void draw_colors()
{
	int pos = 0;
	int y = image->sf->h * 3 + 100;
	print(ed_w+10, y, "Colors");

	y += 30;
	draw_color(y, pos++, 0);

	y += 20;
	draw_color(y, pos++, 254);

	color_pos[pos] = -1;
}


static void draw_color(int y, int pos, int color)
{
	color_pos[pos++] = color;
	
	if(selected_color == pos-1)
	{
		SDL_Rect r1 = { ed_w+6, y-1, screen->w-ed_w-8, 18 };
		SDL_Rect r2 = { ed_w+7, y, screen->w-ed_w-10, 16 };
		SDL_FillRect(screen, &r1, WHITE);
		SDL_FillRect(screen, &r2, BLACK);
	}

	SDL_Rect r = { ed_w+10, y+2, 25, 12 };
	SDL_FillRect(screen, &r, color);
	print(ed_w+43, y, image->imageset->color_name[color]);
}


static int input()
{
	SDL_Event e;
	while(SDL_PollEvent(&e))
	{
		switch(e.type)
		{
		case SDL_QUIT:
			SDL_Quit();
			exit(0);
		case SDL_MOUSEBUTTONDOWN:
			click(e.button.button, e.button.x, e.button.y);
			cursor_active = 0;
			break;
		case SDL_MOUSEMOTION:
			if(e.motion.state == 1 || e.motion.state == 4)
				click(e.motion.state == 1 ? 1 : 3, 
						e.motion.x, e.motion.y);
			break;
		case SDL_KEYDOWN:
			if(e.key.keysym.sym == SDLK_ESCAPE)
				return 1;
			key_press(e.key);
			break;
		}
	}

	return 0;
}


static void click(int b, int x, int y)
{
	if(b == 4)
	{
		change_color(-1);
		return;
	}
	else if(b == 5)
	{
		change_color(1);
		return;
	}

	if(x < ed_w)
	{
		int ix = x / zoom;
		int iy = y / zoom;
		if(ix >= 0 && iy >= 0 && ix < image->sf->w && iy < image->sf->h)
		{
			if(b == 1)
				P(image->sf, ix, iy) = color_pos[selected_color];
			else if(b == 3)
				P(image->sf, ix, iy) = TRANSPARENT;
		}
	}
}


static void key_press(SDL_KeyboardEvent k)
{
	switch(k.keysym.sym)
	{
	case SDLK_DOWN:
		if(cursor_y < image->sf->h - 1)
			++cursor_y;
		cursor_active = 1;
		break;
	case SDLK_UP:
		if(cursor_y > 0)
			--cursor_y;
		cursor_active = 1;
		break;
	case SDLK_RIGHT:
		if(cursor_x < image->sf->w - 1)
			++cursor_x;
		cursor_active = 1;
		break;
	case SDLK_LEFT:
		if(cursor_x > 0)
			--cursor_x;
		cursor_active = 1;
		break;

	case SDLK_SPACE:
		P(image->sf, cursor_x, cursor_y) = color_pos[selected_color];
		break;
	case SDLK_z:
		P(image->sf, cursor_x, cursor_y) = TRANSPARENT;
		break;

	case SDLK_PAGEUP:
		change_color(-1);
		break;
	case SDLK_PAGEDOWN:
		change_color(1);
		break;
	default:
		break;
	}
}


static void change_color(int n)
{
	if(n == -1)
	{
		--selected_color;
		if(selected_color < 0)
		{
			selected_color = 0;
			while(color_pos[++selected_color] != -1);
			--selected_color;
		}
	}
	else if(n == 1)
	{
		++selected_color;
		if(color_pos[selected_color] == -1)
			selected_color = 0;
	}
	else
		abort();
}
