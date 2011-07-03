package trader.ship;

import java.util.HashMap;
import trader.goods.Good;

public abstract class Ship
{
    public ShipClass shipClass = null;
    protected HashMap<Good, Integer> storage = new HashMap<Good, Integer>();
    double integrity = 1.0;
}
