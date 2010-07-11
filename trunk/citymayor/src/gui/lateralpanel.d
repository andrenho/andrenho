// TODO
//   * open and close

module gui.lateralpanel;

import derelict.sdl.sdl;

import gui.defaultgui;
import gui.minimap;
import util.sdl;

class LateralPanel
{
	const ushort widthOpen = 200;
    const ushort minimapMargin = 20;
    const ushort minimapY = 60;

	enum State { OPEN, CLOSED, OPENING, CLOSING };
	State state = State.OPEN;
	MiniMap minimap;

	private
	{
		const ushort widthClosed = 15;
		ushort _w;
		SDL_Surface* sf;
        uint minimapPosX, minimapPosY;
	}
	
	this(uint maxH, DefaultGUI gui, MiniMap minimap)
	{
		this.minimap = minimap;
		_w = widthOpen;

        // draw panel
		sf = SDL_CreateRGBSurface(SDL_SWSURFACE, widthOpen+2, maxH+4, 32, 0, 0, 0, 0);
		fillRectMarble(sf, null);

        // draw minimap
        fillRectMarble(sf, &SDL_Rect(minimapMargin, minimapY, widthOpen-(minimapMargin*2), widthOpen-(minimapMargin*2)), Effect3D.LOWER);
        // TODO - why doesn't the line below works???
        SDL_FillRect(sf, &SDL_Rect(minimapMargin+2, minimapY+2, widthOpen-(minimapMargin*2)-4, widthOpen-(minimapMargin*2))-4, 0);
        minimapPosX = (widthOpen-(minimapMargin*2))/2 - minimap.sf.w/2;
        minimapPosY = (widthOpen-(minimapMargin*2))/2 - minimap.sf.h/2;

        // lateral arrow
		SDL_BlitSurface(gui.images["lateralarrow"], null, sf, &SDL_Rect(4, 6));
	}
	
	void draw(SDL_Surface* screen)
	{
		// TODO - check, maybe don't update every frame
        
        // draw minimap
        minimap.redraw(); // TODO - here???
        SDL_BlitSurface(minimap.sf, null, sf,
                &SDL_Rect(cast(ushort)(minimapMargin+minimapPosX), 
                          cast(ushort)(minimapY+minimapPosY)));

        // draw panel on screen
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
