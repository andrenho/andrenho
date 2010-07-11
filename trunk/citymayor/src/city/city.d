module city.city;

import std.xml, std.string, std.conv, std.stdio;

import city.tile;
import city.structure;
import city.road;

class City
{
	Tile[][] tile;
	uint w, h;
	Structure[] structures;
    string name = "Unnamed";
	
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
	
	
	bool build(Structure structure, Tile tile)
	{
		return addStructureToCity(structure, tile);
	}
	
	
	private
	{
		bool addStructureToCity(Structure structure, Tile tile)
		{
			for(uint x=tile.x; x<(tile.x + structure.dt.w); x++)
				for(uint y=tile.y; y<(tile.y + structure.dt.h); y++)
                    if(this.tile[x][y].structure !is null)
                        return false;

			structure.tile = tile;
			for(uint x=tile.x; x<(tile.x + structure.dt.w); x++)
				for(uint y=tile.y; y<(tile.y + structure.dt.h); y++)
					this.tile[x][y].structure = structure;
			structures ~= structure;
            return true;
		}
	}
	
	
	//
	// Serialization
	//
	
	string serialize()
	{
		string s = "<?xml version=\"1.0\"?>\n";
		s ~= format("<city w=\"%d\" h=\"%d\">\n", w, h);
		
		// tiles
		s ~= "\t<tiles>\n";
		for(uint x; x<w; x++)
			for(uint y; y<h; y++)
				s ~= "\t\t" ~ tile[x][y].serialize() ~ "\n";
		s ~= "\t</tiles>\n";
		
		// structures
		s ~= "\t<structures>\n";
		foreach(Structure structure; structures)
			s ~= "\t\t" ~ structure.serialize() ~ "\n";
		s ~= "\t</structures>\n";
		
		s ~= "</city>";
		return s;
	}

	
	this(Document xml)
	{
		assert(xml.tag.name == "city");
		
		w = to!uint(xml.tag.attr["w"]);
		h = to!uint(xml.tag.attr["h"]);
		tile.length = w;
		for(uint x; x<w; x++)
			tile[x].length = h;

		// tiles
		foreach(Element e; xml.elements)
			if(e.tag.name == "tiles")
				foreach(Element et; e.elements)
				{
					Tile t = new Tile(et);
					tile[t.x][t.y] = t;
				}
			
		// other things
		foreach(Element e; xml.elements)
		{
			switch(e.tag.name)
			{
				case "tiles": break;
				case "structures":
					foreach(Element es; e.elements)
					{
						Structure str;
						switch(es.tag.name)
						{
							case "road":
								str = new Road(es); break;
							default:
								assert(false);
						}
						
						uint x = to!uint(es.tag.attr["x"]);
						uint y = to!uint(es.tag.attr["y"]);
						assert(addStructureToCity(str, tile[x][y]));
					}
					break;
				default:
					assert(false);
			}
		}
	}
}
