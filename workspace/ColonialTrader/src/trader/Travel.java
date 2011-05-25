package trader;
 
import java.util.Stack;

import trader.EnemyShip.CaptainType;

public class Travel {
	
	public static TravelInterface travelInterface;
	public Stack<EnemyShip> encounters = new Stack<EnemyShip>();
	private EnemyShip currentEncounter = null;

	public Travel(City city) {
		int pirates = 0, government = 0, merchants = 0;
		switch(city.type)
		{
		case AGRICULTURAL:
			pirates = 2;
			government = 3;
			merchants = 4;
			break;
		case PROSPECTING:
			pirates = 8;
			government = 2;
			merchants = 7;
			break;
		case INDUSTRIAL:
			pirates = 5;
			government = 4;
			merchants = 5;
			break;
		case URBAN: 
			pirates = 3;
			government = 6;
			merchants = 5;
			break;
		case ARISTOCRATIC:
			pirates = 6;
			government = 8;
			merchants = 6;
			break;
		case PIRATE:
			pirates = 10;
			government = 0;
			merchants = 4;
			break;
		default:
			assert false;
		}
		
		while(pirates + government + merchants > 0)
		{
			if(Math.random() < 1/3)
			{
				pirates--;
				if(pirates >= 0 && Math.random() > 0.8)
					encounters.push(new EnemyShip(CaptainType.PIRATE));
			}
			else if(Math.random() < 2/3)
			{
				government--;
				if(government >= 0 && Math.random() > 0.8)
					encounters.push(new EnemyShip(CaptainType.GOVERNMENT));
			}
			else
			{
				merchants--;
				if(merchants >= 0 && Math.random() > 0.8)
					encounters.push(new EnemyShip(CaptainType.MERCHANT));
			}
		}
	}


	public boolean areWeThereYet() {
		return encounters.isEmpty();
	}

	public void encounter() {
		if(currentEncounter == null)
			currentEncounter = encounters.pop();
		if(currentEncounter != null)
			travelInterface.encounter(currentEncounter);
		currentEncounter = null;
	}

}
