module util.sdl;

import std.random, std.stdio, std.string;

import derelict.sdl.sdl;
import derelict.sdl.ttf;

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
	else if(effect3D == Effect3D.LOWER)
	{
		SDL_FillRect(sf, &SDL_Rect(cast(short)(x+1), cast(short)(y+1), 1, h), colorDark);
		SDL_FillRect(sf, &SDL_Rect(cast(short)(x+1), cast(short)(y+1), w, 1), colorDark);
		SDL_FillRect(sf, &SDL_Rect(cast(short)(x+1), cast(short)(y+h), w, 1), colorLight);
		SDL_FillRect(sf, &SDL_Rect(cast(short)(x+w), cast(short)(y+1), 1, h), colorLight);
		SDL_FillRect(sf, &SDL_Rect(x, y, 1, h), colorDark);
		SDL_FillRect(sf, &SDL_Rect(x, y, w, 1), colorDark);
		SDL_FillRect(sf, &SDL_Rect(x, cast(short)(y+h-1), w, 1), colorLight);
		SDL_FillRect(sf, &SDL_Rect(cast(short)(x+w-1), y, 1, h), colorLight);
	}
	else
		assert(false, "Not implemented");
}


void fillRectMarble(SDL_Surface* sf, SDL_Rect* r, Effect3D effect3D = Effect3D.UPPER)
{
	const uint rock1 = 0xa8a8a8, rock2 = 0xb0b0b0;
	const uint rockLight1 = 0xeeeeee, rockLight2 = 0xdddddd;
	const uint rockDark1 = 0x555555, rockDark2 = 0x666666;
	
	assert(effect3D != Effect3D.BEVEL, "Effect bevel not supported for this kind of operation.");
	if(r is null)
		r = &SDL_Rect(0, 0, cast(ushort)sf.w, cast(ushort)sf.h);
	
	SDL_FillRect(sf, &SDL_Rect(cast(short)(r.x+1), cast(short)(r.y+1), cast(short)(r.w-2), cast(short)(r.h-2)), rock1);
	
	if(SDL_MUSTLOCK(sf))
		SDL_LockSurface(sf);
		
	auto rnd = Random(5);

	for(uint x=r.x; x<r.x+r.w; x++)
		for(uint y=r.y; y<r.y+r.h; y++)
		{
			ubyte *p = cast(ubyte*)sf.pixels + (y*sf.pitch) + (x*4);
			if((x == r.x && y == r.y) || (x == r.x && y == r.y+r.h-1) || (x == r.x+r.w-1 && y == r.y) || (x == r.x+r.w-1 && y == r.y+r.h-1))
			{
				// do nothing
			}
			else if(x < (r.x+2) || y < (r.y+2))
			{
				if(rnd.front > rnd.max * 0.6)
					*cast(uint*)p = (effect3D == Effect3D.UPPER ? rockLight1 : rockDark1);
				else
					*cast(uint*)p = (effect3D == Effect3D.UPPER ? rockLight2 : rockDark2);
			}
			else if(x > (r.x+r.w-3) || y > (r.y+r.h-3))
			{
				if(rnd.front > rnd.max * 0.6)
					*cast(uint*)p = (effect3D == Effect3D.UPPER ? rockDark1 : rockLight1);
				else
					*cast(uint*)p = (effect3D == Effect3D.UPPER ? rockDark2 : rockLight2);
			}
			else if(rnd.front > rnd.max * 0.6)
				*cast(uint*)p = rock2;
			rnd.popFront;
		}
	
	if(SDL_MUSTLOCK(sf))
		SDL_UnlockSurface(sf);
}

const SDL_Color black = {0,0,0};

enum Align { RIGHT, LEFT };

short surfaceWrite(SDL_Surface* sf, string text, ushort x, ushort y, TTF_Font* font, SDL_Color color=black, Align alignment=Align.LEFT)
{
	SDL_Surface* sft = TTF_RenderText_Solid(font, text.toStringz, color);
	if(alignment == Align.RIGHT)
		x -= sft.w;
	SDL_BlitSurface(sft, null, sf, &SDL_Rect(x, y));
	SDL_FreeSurface(sft);
	return cast(short)(TTF_FontLineSkip(font) + y);
}