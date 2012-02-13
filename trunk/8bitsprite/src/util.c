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
