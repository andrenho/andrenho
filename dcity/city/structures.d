module city.structures;

abstract class Structure
{
    uint x, y, w, h;
    bool turned;

    void process();
    string shortDescription();
    string longDescription();
}



