module city.person;

import std.stdio;
import std.array;
import std.math;

import city.city;
import city.moveable;
import city.residence;

const int[Class] threshold;
static this()
{
   threshold = [ Class.LOW: 40, Class.MIDDLE: 70, Class.HIGH: 100, Class.MILLIONAIRE: 140 ];
}

class Person : Moveable
{
    uint salary;
    Class klass;
    Residence residence;
    private
    {
        const float SPEED = 0.1;
        Path currentPath;
        Path[] queue;
    }

    /// Create a new person.
    this(float x, float y, Class klass)
    {
        this.x = x;
        this.y = y;
        this.klass = klass;
        residence = null;
    }


    /// Makes the person move. This is called FPS times per second.
    void move(City city)
    {
        if(currentPath.tiles.empty)
            nextPathInQueue(city);
        if(currentPath.tiles.empty)
            return;

        Tile next = currentPath.tiles[0];
        float dest_x = (cast(float) next.x) + 0.5,
              dest_y = (cast(float) next.y) + 0.5;

        // move
        if(x < dest_x)
            x += SPEED;
        else if(x > dest_x)
            x -= SPEED;
        if(y < dest_y)
            y += SPEED;
        else if(y > dest_y)
            y -= SPEED;
        
        // next step of the path
        if(approxEqual(x, dest_x) && approxEqual(y, dest_y))
            currentPath.tiles.popFront();
    }


    /// The person buys a new residence for himself.
    void buyResidence(Residence r)
    {
        if(r.level == 0)
            r.promote();
        else
            assert(r.dwellers < r.space);
        this.residence = r;
        r.dwellers += 1;
    }


    /// This is called when the person is first created.
    void emmigrate(City city)
    {
        Path path = buildPathTo(city, residence.x, residence.y);
        foreach(Tile tile; path.tiles)
            writefln("%d x %d", tile.x, tile.y);
        currentPath = path;
    }


    private void nextPathInQueue(City city)
    {
    }
}
