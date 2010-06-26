module carengine.map;

import carengine.tile;

class Map
{
    Tile[][] tile;

    this(uint w, uint h)
    {
        tile.length = w;
        for(uint x=0; x<w; x++)
        {
            tile[x].length = h;
            for(uint y=0; y<h; y++)
                tile[x][y] = new Tile(x, y);
        }
    }
}
