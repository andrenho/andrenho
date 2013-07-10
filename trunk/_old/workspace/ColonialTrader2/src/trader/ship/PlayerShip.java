package trader.ship;

import java.util.Vector;
import trader.Formulas;
import trader.people.Mercenary;
import trader.world.City;


public class PlayerShip extends Ship
{
    public Vector<Mercenary> mercenaries = new Vector<Mercenary>();
    public City cityDocked = null;
    
    /** Create the player ship. */
    public PlayerShip(ShipClass shipClass)
    {
        this.shipClass = shipClass;
    }

    /** Get the range of the ship. */
    public double getRange()
    {
        return shipClass.range;
    }
    
    /** Attack a enemy. */
    public void attack(EnemyShip enemy)
    {
        enemy.wasAttacked = true;
        double chanceSucessful = Formulas.sucessfulAttackChance(this.attackStrength(), enemy.defensiveStrength()) * Formulas.randomizer();
        double chanceRebound = 1 - chanceSucessful;
        
        if(chanceSucessful >= 0.5)
            enemy.integrity -= Formulas.damage(this.attackStrength(), enemy.defensiveStrength()) * Formulas.randomizer();
        if(enemy.integrity > 0 && chanceRebound >= 0.5)
            this.integrity -= Formulas.damage(enemy.attackStrength(), this.defensiveStrength()) * Formulas.randomizer();
    }
    
    /** Flee from a enemy. */
    public void flee(EnemyShip enemy)
    {
    }
    
    /** Trade with a merchant. */
    public void trade(EnemyShip enemy)
    {
    }
    
    /** Sumbit to a enemy. */
    public void submit(EnemyShip enemy)
    {
    }
    
    /** Ignore the enemy. */
    public void ignore(EnemyShip enemy)
    {
    }
}
