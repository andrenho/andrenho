module pathfinding.micropather;

import std.stdio;

extern(C++)
{
    interface Map
    {
        float LeastCostEstimate( void* nodeStart, void* nodeEnd );
        void AdjacentCost( void* state, void *adjacent );
        void  PrintStateInfo( void* state );
    }

    Map getMap();
}

void main()
{
    Map g = getMap();
	writefln("Test");
}
