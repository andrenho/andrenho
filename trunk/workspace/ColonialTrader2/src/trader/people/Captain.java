package trader.people;

import trader.ship.PlayerShip;
import trader.ship.ShipClass;

public class Captain
{   
    public final PlayerShip ship = new PlayerShip(ShipClass.CARAVEL);
    public final String name;
    public final Skills skills;
    
    public Captain(String name, Skills skills)
    {
        this.name = name;
        this.skills = skills;
        assert skills.testForPlayer();
    }
}
