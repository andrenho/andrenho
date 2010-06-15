module city.city;

import std.array;

import city.basic;
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
}


class City
{
    private Tile[] _tile;
    Structure[] structures;
    Moveable[] moveables;
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
        searchForImmigrants();
    }

    
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


    private void searchForImmigrants()
    {
        foreach(Structure s; structures)
        {
            Residence r;
            if((r = cast(Residence) s) !is null)
                if(r.dwellers < r.space && r.attractiveness() > threshold[r.klass])
                {
                    auto p = new Person(0.0, 0.0, r.klass);
                    moveables ~= p;
                    p.buyResidence(r);
                    p.emmigrate();
                }
        }
    }
}
