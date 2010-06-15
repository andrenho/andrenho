module city.residence;

import city.basic;

enum Density { LOW, HIGH }

class Residence : Structure
{
    Class klass;
    Density density;
    uint dwellers;
    uint space;
    uint level;

    this(uint x, uint y, bool turned, Class klass, Density density)
    {
        this.x = x;
        this.y = y;
        this.turned = turned;
        this.klass = klass;
        this.density = density;
        dwellers = 0;
        level = 0;

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


    string shortDescription()
    {
        string s;
        if(density == Density.LOW)
            s = "L";
        else
            s = "H";

        final switch(klass)
        {
            case Class.LOW: s ~= "L"; break;
            case Class.MIDDLE: s ~= "M"; break;
            case Class.HIGH: s ~= "H"; break;
            case Class.MILLIONAIRE: s ~= "V"; break;
        }

        return s;
    }


    string longDescription()
    {
        string s;
        if(density == Density.LOW)
            s = "Low density";
        else
            s = "High density";

        s ~= " / ";

        final switch(klass)
        {
            case Class.LOW: s ~= "Low class"; break;
            case Class.MIDDLE: s ~= "Middle class"; break;
            case Class.HIGH: s ~= "High class"; break;
            case Class.MILLIONAIRE: s ~= "Millionaire"; break;
        }

        return s ~ " residence";
    }


    int attractiveness()
    {
        return 150;
    }
}
