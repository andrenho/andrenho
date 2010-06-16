module city.basic;

import city.city;

enum Class { LOW, MIDDLE, HIGH, MILLIONAIRE }
static const Class[] classes = [ Class.LOW, Class.MIDDLE, Class.HIGH, Class.MILLIONAIRE ];

class GameObject
{
}


abstract class Structure : GameObject
{
    uint x, y, w, h;
    bool turned;

    string shortDescription();
    string longDescription();
}


alias Tile[] Path;


abstract class Moveable : GameObject
{
    float x, y;

    Path buildPathTo(uint x, uint y)
    {
        Path p;
        return p;
    }
}
