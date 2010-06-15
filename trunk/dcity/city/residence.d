module city.residence;

import city.basic;

enum Class { LOW, MIDDLE, HIGH, MILLIONAIRE }
enum Density { LOW, HIGH }

class Residence : Structure
{
    Class klass;
    Density density;

    this(Class klass, Density density)
    {
        this.klass = klass;
        this.density = density;

        final switch(klass)
        {
            case Class.LOW:
                if(density == Density.LOW)
                    w = h = 1;
                else
                    w = h = 2;
                break;
            case Class.MIDDLE:
                if(density == Density.LOW)
                    w = h = 2;
                else
                    w = h = 3;
                break;
            case Class.HIGH:
                if(density == Density.LOW)
                    w = h = 3;
                else
                    w = h = 4;
                break;
            case Class.MILLIONAIRE:
                if(density == Density.LOW)
                    w = h = 4;
                else
                    assert(false);
                break;
        }
    }
}
