module city.city;

import city.tile;
import city.structure;

import city.road; // TODO

class City
{
	Tile[][] tile;
	uint w, h;
	Structure[] structures;
	
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
		
		Road r = new Road(Road.data["street"]);
		build(r, tile[2][2]);
	}
	
	
	void build(Structure structure, Tile tile)
	{
		structure.tile = tile;
		for(uint xx=tile.x; xx<(tile.x + structure.dt.w); xx++)
			for(uint yy=tile.y; yy<(tile.y + structure.dt.h); yy++)
				this.tile[xx][yy].structure = structure;
		structures ~= structure;
	}
	
	
	
	string serialize()
	{
		return "";
	}
}
