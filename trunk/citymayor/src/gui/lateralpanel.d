// TODO
//   * open and close

module gui.lateralpanel;

import derelict.sdl.sdl;

import gui.defaultgui;
import util.sdl;

class LateralPanel
{
	const ushort widthOpen = 200;

	private
	{
		const ushort widthClosed = 10;
		ushort _w;
		SDL_Surface* sf;
	}
	
	this(uint maxH, DefaultGUI gui)
	{
		_w = widthOpen;
		sf = SDL_CreateRGBSurface(SDL_SWSURFACE, widthOpen+2, maxH+4, 32, 0, 0, 0, 0);
		fillRectMarble(sf, null);
		SDL_BlitSurface(gui.images["lateralarrow"], null, sf, &SDL_Rect(8, 8));
	}
	
	void draw(SDL_Surface* screen)
	{
		// TODO - check, maybe don't update every frame
		SDL_BlitSurface(sf, null, screen, &SDL_Rect(cast(ushort)(screen.w - _w), -2));
	}
	
	ushort w()
	{
		return _w;
	}
}
