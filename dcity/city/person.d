module city.person;

import std.stdio;
import std.array;
import std.math;

import city.city;
import city.moveable;
import city.residence;
import city.structures;
import city.work;

const int[Class] threshold;
static this()
{
   threshold = [ Class.LOW: 40, Class.MIDDLE: 70, Class.HIGH: 100, Class.MILLIONAIRE: 140 ];
}

enum Action { NOTHING, EMMIGRATING, GOING_TO_WORK, WORKING, GOING_HOME, GOING_OUT, GOING_BACK, 
	RESTING };

class Person : Moveable
{
    uint grade;
    Class klass;
    Residence residence = null;
	Workplace workplace = null;
    Job job = null;
	Action currentAction = Action.NOTHING;
	uint alarm = 0;

    private
    {
        const uint SPEED = 2;
		const uint WORKTIME = 100;
		const uint RESTTIME = 100;
        Path currentPath;
        Path[] queue;
    }

    /// Create a new person.
    this(uint x, uint y, Class klass)
    {
        this.x = x;
        this.y = y;
        this.klass = klass;
		grade = 1;
    }


    /// Makes the person move. This is called FPS times per second.
    void move(City city)
    {
		if(alarm != 0)
		{
			alarm--;
			return;
		}
        if(currentPath.tiles.empty)
            nextAction(city);
        if(currentPath.tiles.empty)
            return;

        Tile next = currentPath.tiles[0];
        uint dest_x = next.x * 100 + 50,
             dest_y = next.y * 100 + 50;

        uint step = city.tile(cast(uint)(x/100), cast(uint)(y/100)).accelerator(this) * SPEED;

        // move
        if(x < dest_x)
            x += step;
        else if(x > dest_x)
            x -= step;
        if(y < dest_y)
            y += step;
        else if(y > dest_y)
            y -= step;
        
        // next step of the path
        if(x == dest_x && y == dest_y)
            currentPath.tiles.popFront();
    }


    /// The person buys a new residence for himself.
    void buyResidence(Residence r)
    {
        if(r.level == 0)
            r.promote();
        else
            assert(r.dwellers < r.space);
        this.residence = r;
        r.dwellers += 1;
    }


    /// This is called when the person is first created.
    void emmigrate(City city)
    {
        Path path = buildPathTo(city, residence);
        currentPath = path;
		currentAction = Action.EMMIGRATING;
    }

	
	uint salary()
	{
		if(job is null)
			return 0;
		else
			return job.salary;
	}


    private void nextAction(City city)
    {
		Structure goOut;
	
		if(job is null)
			lookForJob(city);
		else switch(currentAction)
		{
			case Action.EMMIGRATING:
				currentAction = Action.NOTHING;
				break;
			case Action.NOTHING:
			case Action.RESTING:
				// go to work!
				currentPath = buildPathTo(city, workplace);
				currentAction = Action.GOING_TO_WORK;
				break;
			case Action.GOING_TO_WORK:
				currentAction = Action.WORKING;
				alarm = WORKTIME;
				break;
			case Action.WORKING:
				currentPath = buildPathTo(city, residence);
				currentAction = Action.GOING_HOME;
				break;
			case Action.GOING_HOME:
				goOut = goOutWhere(city);
				if(goOut is null)
				{
					currentAction = Action.RESTING;
					alarm = RESTTIME;
				}
				else
					assert(false);
				break;
		}
    }


    private void lookForJob(City city)
    {
		Workplace w;
		foreach(Structure s; city.structures)
			if((w = cast(Workplace) s) !is null)
				foreach(Job job; w.jobs)
					if(job.worker is null && w.applyForJob(this))
						return;
    }


	private Structure goOutWhere(City city)
	{
		return null;
	}
}
