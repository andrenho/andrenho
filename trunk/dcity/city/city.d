module city.city;

import city.basic;

class Tile
{
    uint x, y;

    this(uint x, uint y)
    {
        this.x = x;
        this.y = y;
    }
}


class City
{
    private Tile[] _tile;
    Structure[] structures;
    uint w, h;

    this(uint w, uint h)
    {
        this.w = w;
        this.h = h;
        _tile.length = w*h;
        for(uint i=0; i<w*h; i++)
            _tile[i] = new Tile(i%w, i/h);
    }

    Tile tile(uint x, uint y)
    {
        int i = x + (y*w);
        if(i < 0 || x >= w || y >= h)
            return null;
        else
            return _tile[i];
    }

    void process()
    {
    }

    void build(Structure structure)
    {
    }
}
