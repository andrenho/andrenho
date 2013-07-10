import std.stdio;
import std.random;
import std.array;

class Tile
{
	uint cost;
	uint x, y;
	
	this(uint x, uint y, uint cost)
	{
		this.x = x;
		this.y = y;
		this.cost = cost;
	}
}


class Map
{
	uint w, h;
	private Tile[] _tile;
	
	this(uint w, uint h)
	{
		this.w = w;
		this.h = h;
		_tile.length = w*h;
		for(int i=0; i<w*h; i++)
			_tile[i] = new Tile(i%w, i/w, 1);
		for(int i=52; i<59; i++)
			_tile[i].cost = 3;
		_tile[65].cost = 3;
		for(int i=70; i<78; i++)
			_tile[i].cost = 3;
	}
	
	Tile tile(uint x, uint y)
	{
		if(x > w)
			return null;
		if(y > h)
			return null;
		return _tile[x+y*w];
	}
	
	void print(Tile[] tiles)
	{
		writef("+");
		for(uint i=0; i<w; i++)
			writef("-");
		writefln("+");
		
		for(uint y=0; y<h; y++)
		{
			writef("|");
			for(uint x=0; x<w; x++)
			{
				Tile t = tile(x, y);
				bool found = false;
				foreach(Tile t2; tiles)
					if(t == t2)
					{
						writef("@");
						found = true;
					}
				if(!found)
					switch(tile(x, y).cost)
					{
						case 0: writef(" "); break;
						case 1: writef("."); break;
						case 2: writef(":"); break;
						case 3: writef("#"); break;
						default: assert(false);
					}
			}
			writefln("|");
		}
		
		writef("+");
		for(uint i=0; i<w; i++)
			writef("-");
		writefln("+");		
	}
	
	
	Tile[] findPath(uint fx, uint fy, uint tx, uint ty)
	{
		float[Tile] dist;
		Tile[Tile] previous;
		
		Tile source = tile(fx, fy);
		Tile target = tile(tx, ty);
		
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
//			writefln("--> %d x %d", u.x, u.y);
			if(dist[u] == uint.max)
				break;
				
			if(u == target)
				break;
				
			Q.remove(u);
//			writefln("-----------");
//			foreach(Tile t, bool b; Q)
//				writefln("%d x %d: %d", t.x, t.y, b);
//			writefln("-----------");
			
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
	
	private Tile[] neighbors(Tile t)
	{
		Tile[] tiles;
		for(int x = (cast(int)t.x-1); x <= (cast(int)t.x+1); x++)
			for(int y = (cast(int)t.y-1); y <= (cast(int)t.y+1); y++)
				if(x >= 0 && x < w && y >= 0 && y < h && tile(x, y) != t)
					tiles ~= tile(x, y);
		return tiles;
	}
	
	private float distanceBetween(Tile u, Tile v)
	{
		if(u.x != v.x && u.y != v.y)
			return 1.4 * v.cost;
		else
			return 1 * v.cost;
	}
}


void main()
{
	Map m = new Map(10, 10);
	Tile[] tiles = m.findPath(0, 0, 8, 9);
	m.print(tiles);
}