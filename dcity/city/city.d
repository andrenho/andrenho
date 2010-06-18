module city.city;

import std.array;
import std.stdio;

import city.moveable;
import city.structures;
import city.person;
import city.residence;

class Tile
{
    uint x, y;
    Structure structure;

    this(uint x, uint y)
    {
        this.x = x;
        this.y = y;
    }

    uint accelerator(Moveable m)
    {
        Street street = cast(Street) structure;
        if(street !is null)
            return street.accelerator;

        return 1;
    }

	uint cost()
	{
		return 1;
	}
}


class City
{
    Structure[] structures;
    Moveable[] moveables;
    uint w, h;

    private Tile[] _tile;
    
    /// Create a new city.
    this(uint w, uint h)
    {
        this.w = w;
        this.h = h;
        _tile.length = w*h;
        for(uint i=0; i<w*h; i++)
            _tile[i] = new Tile(i%w, i/h);
    }


    /// Return a given tile of the city.
    Tile tile(uint x, uint y)
    {
        int i = x + (y*w);
        if(i < 0 || x >= w || y >= h)
            return null;
        else
            return _tile[i];
    }

    
    /// Process everything in the city. This is called FPS times per second.
    void process()
    {
        searchForImmigrants();
        foreach(Structure s; structures)
            s.process();
        foreach(Moveable m; moveables)
            m.move(this);
    }


    /// Build a new structure in the city.
    bool build(Structure structure)
    {
        uint w = structure.turned ? structure.h : structure.w;
        uint h = structure.turned ? structure.w : structure.h;

        for(uint xx=structure.x; xx<(structure.x+w); xx++)
            for(uint yy=structure.y; yy<(structure.y+h); yy++)
                {
                    Tile t = tile(xx,yy);
                    if(t is null || t.structure !is null)
                        return false;
                }

        for(uint xx=structure.x; xx<(structure.x+w); xx++)
            for(uint yy=structure.y; yy<(structure.y+h); yy++)
                tile(xx,yy).structure = structure;

        structures ~= structure;
        return true;
    }


    /// Returns the population of the city.
    uint population()
    {
        uint total = 0;
        Residence r;

        foreach(Structure s; structures)
            if((r = cast(Residence) s) !is null)
                total += r.dwellers;
        return total;
    }


    /// Check if new immigrants are willing to come to the city, and create them.
    private void searchForImmigrants()
    {
        foreach(Structure s; structures)
        {
            Residence r;
            if((r = cast(Residence) s) !is null)
                if((r.dwellers < r.space || r.level == 0) && r.attractiveness() > threshold[r.klass])
                {
                    debug writefln("Citizen emmigrating.");
                    Person p = new Person(0, 0, r.klass);
                    moveables ~= p;
                    p.buyResidence(r);
                    p.emmigrate(this);
                }
        }
    }


	/// Calculate a path from one place to the other
	Tile[] findPath(Tile source, Tile target)
	{
		Tile[] neighbors(Tile t)
		{
			Tile[] tiles;
			for(int x = (cast(int)t.x-1); x <= (cast(int)t.x+1); x++)
				for(int y = (cast(int)t.y-1); y <= (cast(int)t.y+1); y++)
					if(x >= 0 && x < w && y >= 0 && y < h && tile(x, y) != t)
						tiles ~= tile(x, y);
			return tiles;
		}
		
		float distanceBetween(Tile u, Tile v)
		{
			if(u.x != v.x && u.y != v.y)
				return 1.4 * v.cost;
			else
				return 1 * v.cost;
		}

		float[Tile] dist;
		Tile[Tile] previous;
		
		foreach(Tile t; _tile)
		{
			dist[t] = float.max;
			previous[t] = null;
		}
		dist[source] = 0;
		
		bool[Tile] Q;
		for(uint x=0; x<w; x++)
			for(uint y=0; y<h; y++)
				Q[tile(x,y)] = true;
			
		while(Q.length != 0)
		{
			Tile u = null;
			float d = float.max;
			foreach(Tile t, bool b; Q)
			{
				if(u is null)
					u = t;
				if(dist[t] < d)
				{
					d = dist[t];
					u = t;
				}
			}

			if(dist[u] == uint.max)
				break;
				
			if(u == target)
				break;
				
			Q.remove(u);
			
			foreach(Tile v; neighbors(u))
			{
				float alt = dist[u] + distanceBetween(u, v);
				if(alt < dist[v])
				{
					dist[v] = alt;
					previous[v] = u;
				}
			}
		}
		
		Tile[] S;
		Tile u = target;
		while(previous[u])
		{
			S = [u] ~ S;
			u = previous[u];
		}
		
		return S;
	}
	
}
