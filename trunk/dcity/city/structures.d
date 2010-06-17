module city.structures;

abstract class Structure
{
    uint x, y, w, h;
    bool turned;

    void process();
    string shortDescription();
    string longDescription();
}

class Street : Structure
{
    uint accelerator;

    this(uint x, uint y)
    {
        this.x = x;
        this.y = y;
        w = h = 1;
        turned = false;
        accelerator = 5;
    }


    void process()
    {
    }
    
    
    string shortDescription() { return "s"; }
    string longDescription() { return "Street"; }
}
