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

    this(float x, float y, Class klass)
    {
        this.x = x;
        this.y = y;
        this.klass = klass;
        residence = null;
    }


    void buyResidence(Residence r)
    {
        assert(r.dwellers < r.space);
        residence = r;
        r.dwellers += 1;
    }


    void emmigrate()
    {
    }
}
