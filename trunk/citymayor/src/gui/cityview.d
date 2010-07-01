module gui.cityview;

import derelict.sdl.sdl;

import city.city;

class CityView
{
	alias sf this;
	SDL_Surface* sf;
	
	private
	{
		City city;
        SDL_Surface*[string] images;
        uint tile_w, tile_h;
	}
	
	this(City city, SDL_Surface*[string] images)
	{
		this.city = city;
        this.images = images;
        assert(images["land"]);
        tile_w = images["land"].w;
        tile_h = images["land"].h;
        uint w = tile_w * city.w;
        uint h = tile_h * city.h + 200;
        sf = SDL_CreateRGBSurface(SDL_SWSURFACE, w, h, 32, 0, 0, 0, 0);
        redraw();
	}

    void redraw()
    {
        drawBackground();
    }

    private
    {
        void drawBackground()
        {
            float r = 180, g = 228, b = 237;
            float rinc = (255-r) / cast(float)sf.h;
            float ginc = (255-g) / cast(float)sf.h;
            float binc = (255-b) / cast(float)sf.h;

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
    }
}
