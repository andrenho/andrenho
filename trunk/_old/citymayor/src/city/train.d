module city.train;

import city.moveable;
import city.pathable;

class Vehicle : Moveable
{
    mixin Pathable;
}
