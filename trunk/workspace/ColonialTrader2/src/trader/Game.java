package trader;

import trader.people.Captain;
import trader.world.World;

public class Game
{
    public final Captain captain;
    public World world;
    
    public Game(Captain captain)
    {
        this.captain = captain;
        this.world = new World(80, 50);
        captain.ship.cityDocked = world.cities.get((int)(Math.random() * world.cities.size()));
    }
}
