module gui.infobox;

import derelict.sdl.sdl;

import gui.defaultgui;
import city.tile;

class InfoBox
{
	ushort w;
	const ushort h = 160;
	Tile currentlySelectedTile;
	SDL_Surface* sf;
	bool dirty;
	
	this(DefaultGUI gui, ushort w)
	{
		this.w = w;
		select(null);
	}
	
	void select(Tile tile)
	{
		if(tile != currentlySelectedTile)
		{
			if(sf !is null)
				SDL_FreeSurface(sf);
			sf = SDL_CreateRGBSurface(SDL_SWSURFACE|SDL_SRCCOLORKEY, w, h, 32, 0, 0, 0, 0);
			dirty = true;
		}
	}
}