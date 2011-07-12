package trader.world;

import java.util.Vector;

import trader.Formulas;
import trader.people.Captain;
import trader.ship.EnemyShip;
import trader.ship.EnemyShip.Type;

public class Travel
{
    public Vector<EnemyShip> events = new Vector<EnemyShip>();
    
    public Travel(City city, Captain captain)
    {
        initializeTravelEvents(city, captain);
    }
    
    
    private void initializeTravelEvents(City city, Captain captain)
    {
    	double[] r = city.enemyDensity();
    	double density = r[0] + r[1] + r[2];
    	
    	// add enemies
    	int n_enemies = Formulas.numberEnemies(density);
    	for(int i=0; i < n_enemies; i++)
    	{
    		int d = Formulas.enemyType(r);
    		Type type = null;
    		if(d == 0)
    			type = Type.PIRATE;
    		else if(d == 1)
    			type = Type.GOVERNMENT;
    		else if(d == 2)
    			type = Type.MERCHANT;
    		else
    			assert false;
    		events.add(EnemyShip.autoCreate(type, captain, city));
    	}
    }
}
