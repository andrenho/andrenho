// TODO
//   * open and close

module gui.lateralpanel;

import derelict.sdl.sdl;

import gui.defaultgui;
import util.sdl;

class LateralPanel
{
	enum State { OPEN, CLOSED, OPENING, CLOSING };
	const ushort widthOpen = 200;
	State state = State.OPEN;

	private
	{
		const ushort widthClosed = 15;
		ushort _w;
		SDL_Surface* sf;
	}
	
	this(uint maxH, DefaultGUI gui)
	{
		_w = widthOpen;
		sf = SDL_CreateRGBSurface(SDL_SWSURFACE, widthOpen+2, maxH+4, 32, 0, 0, 0, 0);
		fillRectMarble(sf, null);
		SDL_BlitSurface(gui.images["lateralarrow"], null, sf, &SDL_Rect(4, 6));
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
	
	void process()
	{
		final switch(state)
		{
			case State.OPEN:
			case State.CLOSED:
				return;
			case State.CLOSING:
				_w -= 4;
				if(_w <= widthClosed)
				{
					_w = widthClosed;
					state = State.CLOSED;
				}
				break;
			case State.OPENING:
				_w += 4;
				if(_w >= widthOpen)
				{
					_w = widthOpen;
					state = State.OPEN;
				}
				break;
		}
	}
	
	void close()
	{
		state = State.CLOSING;
	}
	
	void open()
	{
		state = State.OPENING;
	}
}
