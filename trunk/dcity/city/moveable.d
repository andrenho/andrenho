module city.moveable;

import city.city;
import city.structures;

enum Class { LOW, MIDDLE, HIGH, MILLIONAIRE }
static const Class[] classes = [ Class.LOW, Class.MIDDLE, Class.HIGH, Class.MILLIONAIRE ];


struct Path
{
    Tile destination;
    Tile[] tiles;
}


abstract class Moveable
{
    uint x, y;

    void move(City city);

    Path buildPathTo(City city, Structure structure)
    {
        Path path;
        uint xd, yd;
		uint x = structure.x, y = structure.y;
        while(xd != x || yd != y)
        {
            if(xd > x)
                xd--;
            else if(xd < x)
                xd++;
            if(yd > y)
                yd--;
            else if(yd < y)
                yd++;
            path.tiles ~= city.tile(xd, yd);
        }
        return path;
    }
}
