module city.basic;

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


abstract class Moveable : GameObject
{
    float x, y;
}
