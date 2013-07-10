package trader.ship;

import java.util.HashMap;
import trader.goods.Good;

public abstract class Ship
{
    public ShipClass shipClass = null;
    protected HashMap<Good, Integer> storage = new HashMap<Good, Integer>();
    double integrity = 1.0;
    
    /** Calculate the attack strength of the ship, between 0.0 (no strength) 
     *  and 1.0 (maximum strength). */
    public double attackStrength()
    {
        return 1.0; // TODO
    }
    
    /** Calculate the defensive strength of the ship, between 0.0 (no defense)
     *  and 1.0 (maximum defense). */
    public double defensiveStrength()
    {
        return 1.0; // TODO
    }
    
    /** Return the integrity of the ship. */
    public double getIntegrity()
    {
        return integrity;
    }
}
