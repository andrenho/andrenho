package trader.ship;

import java.util.Vector;
import trader.goods.Good;
import trader.people.Mercenary;
import trader.world.City;


public class PlayerShip extends Ship
{
    public Vector<Mercenary> mercenaries = new Vector<Mercenary>();
    public City cityDocked = null;
    
    public PlayerShip(ShipClass shipClass)
    {
        this.shipClass = shipClass;
    }
    
    public int buy(Good good, int amount)
    {
        return 0; // TODO
    }

    public int buyAll(Good good)
    {
        return 0; // TODO
    }

    public double getRange()
    {
        return shipClass.range;
    }
}
