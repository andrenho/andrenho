module gui.lateralpanel;

import std.string;

import derelict.sdl.sdl;
import derelict.sdl.ttf;

import gui.defaultgui;
import gui.minimap;
import gui.infobox;
import util.sdl;

import city.city;

class LateralPanel
{
	const ushort widthOpen = 200;
    const ushort minimapMargin = 20;
    const ushort minimapY = 60;

	enum State { OPEN, CLOSED, OPENING, CLOSING };
	State state = State.OPEN;
	MiniMap minimap;
	InfoBox infobox;

	private
	{
		const ushort widthClosed = 15;
		ushort _w;
		SDL_Surface* sf;
        DefaultGUI gui;
        City city;
        const ushort cityInfoX = 25, cityInfoY = 10;
		ushort infoboxY;
        const uint minimapPosX, minimapPosY;
		short financesY;
	}
	
	this(uint maxH, DefaultGUI gui, MiniMap minimap)
	{
		this.minimap = minimap;
        this.gui = gui;
        this.city = gui.city;
		_w = widthOpen;

        // draw panel
		sf = SDL_CreateRGBSurface(SDL_SWSURFACE, widthOpen+2, maxH+4, 32, 0, 0, 0, 0);
		fillRectMarble(sf, null);

        // draw minimap
        fillRectMarble(sf, &SDL_Rect(minimapMargin, minimapY, widthOpen-(minimapMargin*2), widthOpen-(minimapMargin*2)), Effect3D.LOWER);
        // TODO - why doesn't the line below works???
//        SDL_FillRect(sf, &SDL_Rect(minimapMargin, minimapY, widthOpen-(minimapMargin*2)-4, widthOpen-(minimapMargin*2))-4, 0);
        minimapPosX = (widthOpen-(minimapMargin*2))/2 - minimap.sf.w/2;
        minimapPosY = (widthOpen-(minimapMargin*2))/2 - minimap.sf.h/2;

		// draw finances box
		financesY = cast(short)(minimapY + widthOpen-(minimapMargin*2))+10;
		fillRectMarble(sf, &SDL_Rect(minimapMargin, financesY, widthOpen-(minimapMargin*2), 60), Effect3D.LOWER);
		
		// draw info box
		infoboxY = cast(ushort)(financesY + 70);
		infobox = new InfoBox(gui, widthOpen-(minimapMargin*2));

        // lateral arrow
		SDL_BlitSurface(gui.images["lateralarrow"], null, sf, &SDL_Rect(4, 6));
	}
	
	void draw(SDL_Surface* screen)
	{
		// TODO - check, maybe don't update every frame
        
        // city info
		short y = cast(short)(surfaceWrite(sf, city.name, cityInfoX, cityInfoY, gui.pico));
		y = surfaceWrite(sf, format("pop. %d", city.population), cityInfoX, y, gui.titleSmall);
		y = surfaceWrite(sf, format("City funds: $%d", city.funds), cityInfoX, y, gui.titleSmall);

        // draw minimap
        minimap.redraw(); // TODO - here???
        SDL_BlitSurface(minimap.sf, null, sf,
                &SDL_Rect(cast(ushort)(minimapMargin+minimapPosX), 
                          cast(ushort)(minimapY+minimapPosY)));
		y = cast(short)(minimapY + widthOpen-(minimapMargin*2));

		// city fincances
		uint expenses = city.monthlyExpenses, income = city.monthlyIncome;
		surfaceWrite(sf, "M. Income", cast(short)(minimapMargin+4), cast(short)(financesY+4), 
				gui.titleSmall, SDL_Color(0, 0, 220));
		y = surfaceWrite(sf, format("$%d", income), cast(short)(widthOpen-(minimapMargin*2)+4), cast(short)(financesY+4), 
				gui.titleSmall, SDL_Color(0, 0, 220), Align.RIGHT);
		surfaceWrite(sf, "M. Expenses", cast(short)(minimapMargin+4), y, 
				gui.titleSmall, SDL_Color(168, 0, 0));
		y = surfaceWrite(sf, format("$%d", expenses), cast(short)(widthOpen-(minimapMargin*2)+4), y,
				gui.titleSmall, SDL_Color(168, 0, 0), Align.RIGHT);
		SDL_FillRect(sf, &SDL_Rect(cast(short)(minimapMargin+8), cast(short)(y+4), widthOpen-(minimapMargin*2)-16, 1), 0);
		SDL_Color colorBalance;
		if(expenses > income)
			colorBalance = SDL_Color(168, 0, 0);
		else if(expenses < income)
			colorBalance = SDL_Color(0, 0, 220);
		else
			colorBalance = SDL_Color(0, 0, 0);
		surfaceWrite(sf, "Balance", cast(short)(minimapMargin+4), cast(short)(y+10), 
				gui.titleSmall, colorBalance);
		surfaceWrite(sf, format("$%d", income-expenses), cast(short)(widthOpen-(minimapMargin*2)+4), cast(short)(y+10),
				gui.titleSmall, colorBalance, Align.RIGHT);
		
		// infobox
		fillRectMarble(sf, &SDL_Rect(minimapMargin, infoboxY, infobox.w, infobox.h), Effect3D.LOWER);
		if(infobox.dirty)
		{
			SDL_BlitSurface(infobox.sf, null, screen, &SDL_Rect(cast(short)(minimapMargin+2), cast(short)(infoboxY+2)));
			infobox.dirty = false;
		}

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
