// TODO - ampersand for keyboard

module gui.dialog;

import std.stdio, std.string;

import derelict.sdl.sdl;
import derelict.sdl.ttf;

import gui.defaultgui;
import util.sdl;

class Dialog
{
	enum Image { QUESTION, WARNING };
	
	private
	{
		TTF_Font* font;
		SDL_Surface* screen;
		const uint buttonSeparator = 40;
	}
	
	
	this(DefaultGUI gui)
	{
		font = gui.titleFont;
		screen = gui.screen;
	}
	
	
	bool yesNo(string question, Image image = Image.QUESTION, bool _default = true)
	{
		switch(dialog(question, ["Yes", "No"], image, _default ? 0 : 1))
		{
			case 0:
				return true;
			case 1:
				return false;
			default:
				assert(false, "Reply must be 0 or 1");
		}
	}
	
	
	uint dialog(string question, string[] options, Image image, uint _default=0)
	{
		// discover dialog size
		string[] lines = question.wrap(50).split("\n");
		ushort h = cast(ushort)(100 + (lines.length * TTF_FontLineSkip(font)));
		ushort w;
		
		SDL_Surface*[] imageOptions;
		ushort bw = 50, maxOptW = 0;
		foreach(string option; options)
		{
			SDL_Surface* img = TTF_RenderText_Solid(font, option.toStringz(), SDL_Color(0, 0, 0));
			assert(img);
			imageOptions ~= img;
			bw += img.w + 30;
			if(img.w > maxOptW)
				maxOptW = cast(ushort)img.w;
		}
		if(bw < 600)
			w = 600;
		else
			w = bw;
		
		// draw window
		short x = cast(short)(screen.w/2-w/2);
		short y = cast(short)(screen.h/2-h/2);
		fillRectMarble(screen, &SDL_Rect(x, y, w, h));
		
		//draw text
		y += 32;
		foreach(string line; lines)
		{
			SDL_Surface* img = TTF_RenderText_Solid(font, line.toStringz(), SDL_Color(0, 0, 0));
			SDL_BlitSurface(img, null, screen, &SDL_Rect(cast(short)(x+60), y));
			y += TTF_FontLineSkip(font);
		}
		
		// draw options
		SDL_Rect[] areas;
		y += 20;
		x = cast(short)((screen.w/2) - (imageOptions.length * (maxOptW / 2 + buttonSeparator / 2)));
		foreach(SDL_Surface* img; imageOptions)
		{
			SDL_Rect r = { cast(short)(x+(img.w/2)-(maxOptW/2)-10), cast(short)(y-10), cast(short)(maxOptW+20), cast(short)(img.h+20) };
			areas ~= r;
			fillRectMarble(screen, &r);
			SDL_BlitSurface(img, null, screen, &SDL_Rect(x, y));
			x += maxOptW + buttonSeparator;
		}
				
		SDL_Flip(screen);

		// handle events
		SDL_Event e;
		while(true)
		{
			SDL_WaitEvent(&e);
			if(e.type == SDL_MOUSEBUTTONDOWN)
			{
				uint i = 0;
				foreach(SDL_Rect area; areas)
				{
					if(e.button.x >= area.x && e.button.x < (area.x + area.w)
					&& e.button.y >= area.y && e.button.y < (area.y + area.h))
						return i;
					i++;
				}
			}
			else if(e.type == SDL_KEYDOWN)
			{
				if(e.key.keysym.sym == SDLK_RETURN || e.key.keysym.sym == SDLK_KP_ENTER)
					return _default;
			}
		}
	}
}