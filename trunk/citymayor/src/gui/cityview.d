module gui.cityview;

import derelict.sdl.sdl;

import gui.defaultgui;
import city.city;
import city.tile;

class CityView
{
	alias sf this;
	SDL_Surface* sf, background;
    bool displayGrid = false;
	
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
		background = createBackground(w, h);
        sf = SDL_CreateRGBSurface(SDL_SWSURFACE, w, h, 32, 0, 0, 0, 0);
        redraw();
	}

    void redraw()
    {
        drawBackground();
		
        for(uint x=0; x < city.w; x++)
            for(uint y=0; y < city.h; y++)
                drawTile(city.tile[x][y]);
		version(test)
			SDL_FillRect(sf, null, SDL_MapRGB(sf.format, 255, 255, 255));
    }

    private
    {
		// TODO - make it faster
        SDL_Surface* createBackground(uint w, uint h)
        {
			SDL_Surface* bg = SDL_CreateRGBSurface(SDL_SWSURFACE, w, h, 32, 0, 0, 0, 0);
			
            float r = 180, g = 228, b = 237;
            const float rinc = (255-r) / cast(float)bg.h;
            const float ginc = (255-g) / cast(float)bg.h;
            const float binc = (255-b) / cast(float)bg.h;

			if(SDL_MUSTLOCK(bg))
				SDL_LockSurface(bg);

			version(test) {} else
            for(uint y=0; y<bg.h; y++)
            {
                for(uint x=0; x<bg.w; x++)
                {
                    ubyte *p = cast(ubyte*)bg.pixels + (y*bg.pitch) + (x*4);
                    *cast(uint*)p = cast(uint)r * 0x10000 + 
                                    cast(uint)g * 0x100 +
                                    cast(uint)b;
                }
                r += rinc;
                g += ginc;
                b += binc;
            }

			if(SDL_MUSTLOCK(bg))
				SDL_UnlockSurface(bg);
			
			return bg;
        }

		void drawBackground()
		{
			SDL_BlitSurface(background, null, sf, null);
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
                if(displayGrid)
                {
                    SDL_Rect r2 = { cast(short)(x+(tile_w/2)), cast(short)y };
                    SDL_BlitSurface(images["grid"], null, sf, &r);
                }

            }
        }
    }
}
