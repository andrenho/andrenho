module gui.minimap;

import derelict.sdl.sdl;

import city.city, city.tile;

class MiniMap
{
    ushort m = 3; // multiplier

    SDL_Surface* sf;
	
	private
	{
		City city;
	}
	

	this(City city)
	{
		this.city = city;
        sf = SDL_CreateRGBSurface(SDL_SWSURFACE, city.w*m, city.h*m, 32, 0, 0, 0, 0);
	}


    void redraw()
    {
        // TODO - this can be done faster by only updating the dirty tiles
        for(ushort x=0; x<city.w; x++)
            for(ushort y=0; y<city.h; y++)
                SDL_FillRect(sf, 
                        &SDL_Rect(cast(short)(x*m), cast(short)(y*m), m, m), 
                        color(city.tile[x][y]));
    }


    uint color(Tile tile)
    {
        if(tile.structure is null)
            return 0x3c8852;
        else
            assert(0, "Invalid color for minimap");
    }
}
