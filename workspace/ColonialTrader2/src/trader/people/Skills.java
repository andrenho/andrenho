package trader.people;

public class Skills
{
    public final int trader, sailor, fighter, shipwright;
    
    public Skills(int trader, int sailor, int fighter, int shipwright)
    {
        this.trader = trader;
        this.sailor = sailor;
        this.fighter = fighter;
        this.shipwright = shipwright;
    }

    /** Test if the skills are valid for a player. */
    public boolean testForPlayer()
    {
        return true;
    }
}
