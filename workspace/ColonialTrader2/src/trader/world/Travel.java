package trader.world;

import java.util.Vector;
import trader.people.Captain;
import trader.ship.EnemyShip;

public class Travel
{
    private final static int PIRATES = 0, GOVERNMENT = 1, MERCHANTS = 2;
    
    public Vector<EnemyShip> events = new Vector<EnemyShip>();
    
    public Travel(City city, Captain captain)
    {
        initializeTravelEvents(city, captain);
    }
    
    
    private void initializeTravelEvents(City city, Captain captain)
    {
        int[] enemies = city.numberOfEnemies();
        while((enemies[PIRATES] + enemies[GOVERNMENT] + enemies[MERCHANTS]) > 0)
        {
            int n = (int)(Math.random() * 3);
            if(enemies[n] > 0)
            {
                addEvent(n, captain);
                --enemies[n];
            }
        }
    }


    private void addEvent(int n, Captain captain)
    {
        
        
    }
}
