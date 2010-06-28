module city.city;

import city.tile;

class City
{
	Tile[][] tile;
	uint w, h;
	
	this(uint w, uint h)
	{
		this.w = w;
		this.h = h;
		tile.length = w;
		for(uint x; x<w; x++)
		{
			tile[x].length = h;
			for(uint y; y<h; y++)
				tile[x][y] = new Tile(x, y);
		}
	}
}
