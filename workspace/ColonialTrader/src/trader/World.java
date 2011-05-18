package trader;

import java.util.Vector;

public class World {

	public final Vector<City> cities = new Vector<City>();;
	public final int w = 100, h = 80; 
	public boolean[][] land = new boolean[w][h];
	
	public World()
	{
		for(int x=0; x<w; x++)
			for(int y=0; y<h; y++)
				land[x][y] = false;
		
		createIslands();
		createCities();
		adjustDistances();
	}

	private void createIslands() 
	{
		while(amountWater() > 0.65)
		{
			System.out.println(amountWater());
			int x = (int) (Math.random() * w);
			int y = (int) (Math.random() * h);
			int size = (int) (Math.random() * 10 + 1);
			createIsland(x, y, size);
		}
	}
	
	private void createIsland(int ix, int iy, int size) 
	{
		int xx = ix, yy = iy;
		for(int i=0; i<size; i++)
		{
			for(int x=-2; x<=2; x++)
				for(int y=-2; y<=2; y++)
					if(!(x==-2 && y==-2) && !(x==-2 && y==2) && !(x==2 && y==-2) && !(x==2 && y==2))
						setLand(x+xx, y+yy);
			xx += (Math.random() * 3) - 1;
			yy += (Math.random() * 3) - 1;
		}
	}

	private void setLand(int x, int y) {
		if(x >= 0 && x < w && y >= 0 && y < h)
			land[x][y] = true;
	}

	private double amountWater() {
		double water = 0;
		for(int x=0; x<w; x++)
			for(int y=0; y<h; y++)
				if(!land[x][y])
					water += 1;
		return water / (double)(w*h);
	}

	private void createCities() {
		for(int i=0; i<30; i++)
		{
			int x, y;
			do
			{
				x = (int) (Math.random() * w);
				y = (int) (Math.random() * h);
			} while(!hasBeach(x, y));
			cities.add(new City(new Coordinate(x, y)));
		}
	}

	private boolean hasBeach(int x, int y) {
		if(!land[x][y])
			return false;
		for(int xx=x-1; xx<=x+1; xx++)
			for(int yy=y-1; yy<=y+1; yy++)
				if(xx >= 0 && xx < w && yy >= 0 && yy < h)
					if(!land[xx][yy])
						return true;
		return false;
	}

	private void adjustDistances() {
		// TODO Auto-generated method stub
		
	}

}
