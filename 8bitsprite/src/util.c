#include "util.h"

int print(int x, int y, char* fmt, ...)
{
	char buffer[1024];
	va_list args;
	va_start(args, fmt);
	vsprintf(buffer, fmt, args);

	SDL_Color color={255,255,255};
	SDL_Surface *txt = TTF_RenderUTF8_Solid(font, buffer, color);
	SDL_Rect r = { x, y, 0, 0 };
	SDL_BlitSurface(txt, NULL, screen, &r);
	SDL_FreeSurface(txt);

	va_end(args);

	return y + TTF_FontLineSkip(font);
}


int ask_yn(char* question)
{
	SDL_FillRect(screen, NULL, BLACK);
	print(10, 10, question);
	SDL_Flip(screen);

	SDL_Event e;
	for(;;)
		while(SDL_WaitEvent(&e))
			if(e.type == SDL_KEYDOWN)
			{
				if(e.key.keysym.sym == SDLK_y)
					return -1;
				else
					return 0;
			}
}


SDL_Rect* draw_buttons(char* fmt, ...)
{
	va_list ap;
	char* s;
	int y = screen->h - 48;
	int x = 10;
	int n_buttons = 0;
	SDL_Color color={255,255,255};
	SDL_Rect* rects = NULL;

	va_start(ap, fmt);
	s = fmt;
	do
	{
		SDL_Surface* txt = TTF_RenderUTF8_Solid(font, s, color);
		SDL_Rect r = { x, y, txt->w + 20, txt->h + 20 };
		SDL_Rect r2 = { x+1, y+1, txt->w + 18, txt->h + 18 };
		SDL_Rect r3 = { x+10, y+10 };
		SDL_FillRect(screen, &r, WHITE);
		SDL_FillRect(screen, &r2, BLACK);
		SDL_BlitSurface(txt, NULL, screen, &r3);
		SDL_FreeSurface(txt);
		s = va_arg(ap, char *);
		x += txt->w + 30;
		n_buttons++;

		rects = realloc(rects, sizeof(SDL_Rect) * n_buttons);
		memcpy(&rects[n_buttons-1], &r, sizeof(SDL_Rect));
	} while(s);
	va_end(ap);

	return rects;
}
