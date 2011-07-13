package trader.ship;

import trader.Formulas;
import trader.people.Captain;
import trader.world.City;


public class EnemyShip extends Ship
{
	public enum Type { PIRATE, GOVERNMENT, MERCHANT };
	public Type type;
	public boolean wasAttacked = false;
	
	protected EnemyShip(Type type, ShipClass shipClass)
	{
		this.type = type;
		this.shipClass = shipClass;
	}
	
	
	public static EnemyShip autoCreate(Type type, Captain captain, City destination)
	{
		double enemyLevel = Formulas.enemyLevel(captain.getLevel(), destination.getLevel(type));
		double enemyDamage = Formulas.enemyDamage();
		
		ShipClass shipClass = ShipClass.classes[(int)(enemyLevel * ShipClass.classes.length)]; 
		EnemyShip e = new EnemyShip(type, shipClass);
		e.integrity = enemyDamage;
		return e;
	}
}
