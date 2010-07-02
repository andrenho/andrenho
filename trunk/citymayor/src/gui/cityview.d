module gui.cityview;

import derelict.sdl.sdl;

import city.city;
import city.tile;

class CityView
{
	alias sf this;
	SDL_Surface* sf;
	
	private
	{
		City city;
        SDL_Surface*[string] images;
        uint tile_w, tile_h;
        const wspace = 50;
        const hspace = 100;
	}
	
	this(City city, SDL_Surface*[string] images)
	{
		this.city = city;
        this.images = images;
        assert(images["land"]);
        tile_w = images["land"].w + 2;
        tile_h = images["land"].h;
        uint w = (tile_w/2 * city.w) + (tile_w/2 * city.h) + (wspace*2);
        uint h = (tile_h/2 * city.w) + (tile_h/2 * city.h) + (hspace*2);
        sf = SDL_CreateRGBSurface(SDL_SWSURFACE, w, h, 32, 0, 0, 0, 0);
        redraw();
	}

    void redraw()
    {
        drawBackground();
        for(uint x=0; x < city.w; x++)
            for(uint y=0; y < city.h; y++)
                drawTile(city.tile[x][y]);
		//SDL_Rect r = { 10, 10, cast(short)(sf.w-20), cast(short)(sf.h-20) };
		//SDL_FillRect(sf, &r, SDL_MapRGB(sf.format, 255, 255, 255));
		//SDL_Rect r2 = { 50, 50, 10, 10 };
		//SDL_FillRect(sf, &r2, 0);
    }

    private
    {
        void drawBackground()
        {
            float r = 180, g = 228, b = 237;
            const float rinc = (255-r) / cast(float)sf.h;
            const float ginc = (255-g) / cast(float)sf.h;
            const float binc = (255-b) / cast(float)sf.h;

            for(uint y=0; y<sf.h; y++)
            {
                for(uint x=0; x<sf.w; x++)
                {
                    ubyte *p = cast(ubyte*)sf.pixels + (y*sf.pitch) + (x*4);
                    *cast(uint*)p = cast(uint)r * 0x10000 + 
                                    cast(uint)g * 0x100 +
                                    cast(uint)b;
                }
                r += rinc;
                g += ginc;
                b += binc;
            }
        }

        void drawTile(Tile tile)
        {
            uint x = (tile_w/2 * city.h) - (tile_w/2 * tile.y) + 
                (tile_w/2 * tile.x) + wspace - (tile_w/2);
            uint y = (tile_h/2 * tile.y) + (tile_h/2 * tile.x) + hspace -
                tile_h/2;
            if(tile.structure is null)
            {
                SDL_Rect r = { cast(short)x, cast(short)y };
                SDL_BlitSurface(images["land"], null, sf, &r);
                SDL_Rect r2 = { cast(short)(x+(tile_w/2)), cast(short)y };
                SDL_BlitSurface(images["grid"], null, sf, &r);
            }
        }
    }
}
