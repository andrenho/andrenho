module city.farm;

import city.work;

abstract class Farm : Industry
{
    this(uint x, uint y)
    {
        super(x, y);
        w = h = 6;
        turned = false;
		for(int i=0; i<6; i++)
			jobs ~= new Job(1, 400);
    }
}


class VegetableFarm : Farm
{
    this(uint x, uint y)
    {
        super(x, y);
    }

    void process()
    {
    }

    string shortDescription() { return "VFarm"; }
    string longDescription() { return "Vegetable Farm"; }
}
