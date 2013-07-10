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
        path.destination = city.tile(structure.x, structure.y);
		path.tiles = city.findPath(city.tile(x, y), path.destination);
        return path;
    }
}
