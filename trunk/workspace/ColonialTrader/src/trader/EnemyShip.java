package trader;

public class EnemyShip extends Ship {

	/** If the captain is computer or human controlled, and the faction. */ 
	public final CaptainType captainType;
	public enum CaptainType { PIRATE, MERCHANT, GOVERNMENT };
	
	/** Create a new ship (computer controlled). */
	public EnemyShip(CaptainType captainType)
	{
		this.captainType = captainType;
		autoGenerate();
		assert shipClass != null;
	}
	
	/** Auto-generate a enemy ship. */
	private void autoGenerate() 
	{
		double enemyStrength = Captain.getCaptain().ship.overallStrength() + Math.random() / 2 - 0.3; // TODO - dificulty
		if(enemyStrength < 1/6)
			this.shipClass = ShipClass.CARAVEL;
		else if(enemyStrength < 2/6)
			this.shipClass = ShipClass.MARCHANTMAN;
		else if(enemyStrength < 3/6)
			this.shipClass = ShipClass.GALEON;
		else if(enemyStrength < 4/6)
			this.shipClass = ShipClass.PRIVATEER;
		else if(enemyStrength < 5/6)
			this.shipClass = ShipClass.FRIGATE;
		else
			this.shipClass = ShipClass.MAN_O_WAR;
	}

}
