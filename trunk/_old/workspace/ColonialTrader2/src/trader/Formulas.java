package trader;

public class Formulas {

	/** Returns the hardness of the enemy based on the captain level. */
	public static double enemyLevel(double captainLevel, double cityHardness)
	{
		return Math.random(); // TODO
	}
	
	/** Returns the level of damage of a new enemy. */
	public static double enemyDamage()
	{
		double n = Math.random() + 0.5;
		if(n >= 1)
			return 1.0;
		else
			return n;
	}

	/** Return the number of enemies based on the enemy density of the city. */
	public static int numberEnemies(double density) {
		return (int)(density * 8); // TODO
	}

	
	/** Return the type of enemy, based on the density. */
	public static int enemyType(double[] r) {
		double density = r[0] + r[1] + r[2];
    	double[] proportional = {
    			r[0] / density,
    			r[1] / density,
    			r[2] / density
    	};
    	
    	double rnd = Math.random();
    	if(rnd < proportional[0])
    		return 0;
    	else if(rnd < (proportional[0] + proportional[1]))
    		return 1;
    	else
    		return 2;
    }

	/** Calculate the chance of a sucessful attack against a enemy. */
    public static double sucessfulAttackChance(double attack, double defense)
    {
        return (attack-defense) * 2 + 0.5;
    }

    // TODO
    public static double randomizer()
    {
        return 1.0; // TODO
    }

    /** Calculate the amount of damage caused by a attack. */
    public static double damage(double attackStrength, double defensiveStrength)
    {
        return sucessfulAttackChance(attackStrength, defensiveStrength);
    }
	
}
