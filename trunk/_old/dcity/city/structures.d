module city.structures;

abstract class Structure
{
    uint x, y, w, h;
    bool turned;

    this(uint x, uint y)
    {
        this.x = x;
        this.y = y;
    }

    void process();
    string shortDescription();
    string longDescription();
}


class Street : Structure
{
    uint accelerator;

    this(uint x, uint y)
    {
        super(x, y);
        w = h = 1;
        turned = false;
        accelerator = 5;
    }


    void process()
    {
    }
    
    
    string shortDescription() { return " "; }
    string longDescription() { return "Street"; }
}
