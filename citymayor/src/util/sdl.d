module util.sdl;

import derelict.sdl.sdl;

enum Effect3D { BEVEL, UPPER, LOWER };

void draw3DBox(SDL_Surface* sf, short x, short y, ushort w, ushort h, uint colorLight, 
		uint colorDark, Effect3D effect3D = Effect3D.LOWER)
{
	if(effect3D == Effect3D.BEVEL)
	{
		SDL_FillRect(sf, &SDL_Rect(cast(short)(x+1), cast(short)(y+1), 1, h), colorDark);
		SDL_FillRect(sf, &SDL_Rect(cast(short)(x+1), cast(short)(y+1), w, 1), colorDark);
		SDL_FillRect(sf, &SDL_Rect(cast(short)(x+1), cast(short)(y+h), w, 1), colorDark);
		SDL_FillRect(sf, &SDL_Rect(cast(short)(x+w), cast(short)(y+1), 1, h), colorDark);
		SDL_FillRect(sf, &SDL_Rect(x, y, 1, h), colorLight);
		SDL_FillRect(sf, &SDL_Rect(x, y, w, 1), colorLight);
		SDL_FillRect(sf, &SDL_Rect(x, cast(short)(y+h-1), w, 1), colorLight);
		SDL_FillRect(sf, &SDL_Rect(cast(short)(x+w-1), y, 1, h), colorLight);
	}
	else
		assert(false);
}