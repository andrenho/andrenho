module city.person;

import city.basic;
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
    Path currentPath = null;

    this(float x, float y, Class klass)
    {
        this.x = x;
        this.y = y;
        this.klass = klass;
        residence = null;
    }


    void move()
    {
    }


    void buyResidence(Residence r)
    {
        if(r.level == 0)
            r.promote();
        else
            assert(r.dwellers < r.space);
        this.residence = r;
        r.dwellers += 1;
    }


    void emmigrate()
    {
        Path path = buildPathTo(residence.x, residence.y);
    }
}
