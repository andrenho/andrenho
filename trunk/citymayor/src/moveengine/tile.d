module carengine.tile;

class Tile
{
    uint x, y;
    uint _maxspeed = 20;

    this(uint x, uint y)
    {
        this.x = x;
        this.y = y;
    }

    uint maxSpeed()
    {
        return _maxspeed;
    }
}
