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
        const uint SPEED = 2;
        Path currentPath;
        Path[] queue;
    }

    /// Create a new person.
    this(uint x, uint y, Class klass)
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
        uint dest_x = next.x * 100 + 50,
             dest_y = next.y * 100 + 50;

        uint step = city.tile(cast(uint)(x/100), cast(uint)(y/100)).accelerator(this) * SPEED;

        // move
        if(x < dest_x)
            x += step;
        else if(x > dest_x)
            x -= step;
        if(y < dest_y)
            y += step;
        else if(y > dest_y)
            y -= step;
        
        // next step of the path
        if(x == dest_x && y == dest_y)
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
        /*
        foreach(Tile tile; path.tiles)
            writefln("%d x %d", tile.x, tile.y);
        */
        currentPath = path;
    }


    private void nextPathInQueue(City city)
    {
    }
}
