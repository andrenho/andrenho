package trader;

import java.util.HashMap;
import java.util.Vector;

public class World {

	/** Vector containing the cities in the map */
	public final Vector<City> cities = new Vector<City>();
	
	/** Map width */
	public static final int w = 100;
	
	/** Map height */
	public static final int h = 80;
	public final int n_cities = 50;
	public boolean[][] land = new boolean[w][h];
	

	/** Create a new world. */
	public World()
	{
		for(int x=0; x<w; x++)
			for(int y=0; y<h; y++)
				land[x][y] = false;
		
		createIslands();
		createCities();
		adjustDistances();
	}

	/** Create all the islands in the world. */
	private void createIslands() 
	{
		while(amountWater() > 0.65)
		{
			int x = (int) (Math.random() * w);
			int y = (int) (Math.random() * h);
			int size = (int) (Math.random() * 10 + 1);
			createIsland(x, y, size);
		}
	}
	
	/** Create one island. */
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

	/** Set a given tile as land. */
	private void setLand(int x, int y) {
		if(x >= 0 && x < w && y >= 0 && y < h)
			land[x][y] = true;
	}

	/** Calculate the amount (%) of water in the map. */
	private double amountWater() {
		double water = 0;
		for(int x=0; x<w; x++)
			for(int y=0; y<h; y++)
				if(!land[x][y])
					water += 1;
		return water / (double)(w*h);
	}

	/** Create all cities. */
	private void createCities() {
		for(int x=0; x<w; x += w / Math.sqrt(n_cities))
			for(int y=0; y<h; y += h / Math.sqrt(n_cities))
			{
				int xx, yy, tries = 100;
				do
				{
					xx = (int) (Math.random() * w / Math.sqrt(n_cities)) + x;
					if(xx >= w)
						xx = w-1;
					yy = (int) (Math.random() * h / Math.sqrt(n_cities)) + y;
					if(yy >= h)
						yy = h-1;
					if(tries-- < 0)
						break;
				} while(!hasBeach(xx, yy));
				if(hasBeach(xx, yy))
					cities.add(new City(new Coordinate(xx, yy)));
			}
	}

	/** Detect if a given tile is a beach. */
	private boolean hasBeach(int x, int y) 
	{
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
	
	
	/** Calculate the path between two points in the map, going only through the sea. */
	public Vector<Coordinate> pathBetweenCoordinates(Coordinate start, Coordinate goal) 
	{
		Vector<Coordinate> closedset = new Vector<Coordinate>();
		Vector<Coordinate> openset = new Vector<Coordinate>();
		HashMap<Coordinate, Coordinate> camefrom = new HashMap<Coordinate, Coordinate>();
		
		HashMap<Coordinate, Integer> g_score = new HashMap<Coordinate, Integer>(),
		                             h_score = new HashMap<Coordinate, Integer>(),
		                             f_score = new HashMap<Coordinate, Integer>();
		
		openset.add(start);
		g_score.put(start, 0);
		h_score.put(start, estimateCost(start, goal));
		f_score.put(start, h_score.get(start));
		
		while(!openset.isEmpty())
		{
			Coordinate x = null;
			int sc = Integer.MAX_VALUE;
			for(Coordinate c: openset)
				if(f_score.get(c) < sc)
				{
					sc = f_score.get(c);
					x = c;
				}
			
			if(x.equals(goal))
				return reconstructPath(camefrom, camefrom.get(goal));
			
			openset.remove(x);
			closedset.add(x);
			for(Coordinate y: neighborNodes(x, start, goal))
			{
				if(closedset.contains(y))
					continue;
				int tentative_g_score = g_score.get(x) + estimateCost(x,y);
				
				boolean tentative_is_better;
				if(!openset.contains(y))
				{
					openset.add(y);
					tentative_is_better = true;
				}
				else if(tentative_g_score < g_score.get(y))
					tentative_is_better = true;
				else
					tentative_is_better = false;
				
				if(tentative_is_better)
				{
					camefrom.put(y, x);
					g_score.put(y, tentative_g_score);
					h_score.put(y, estimateCost(y, goal));
					f_score.put(y, g_score.get(y) + h_score.get(y));
				}
			}
		}
		
		return null;
	}

	/** Pathfinder helper function. */
	private Vector<Coordinate> neighborNodes(Coordinate c, Coordinate start, Coordinate goal) {
		Vector<Coordinate> v = new Vector<Coordinate>();
		int t = 0;
		for(int x=-1; x<=1; x++)
			for(int y=-1; y<=1; y++)
				if(c.x+x >= 0 && c.y+y >=0 && c.x+x < w && c.y+y < h && !(x==0 && y==0))
					if(!land[c.x+x][c.y+y] || c.near(goal) || c.near(start))
					{
						t++;
						v.add(new Coordinate(c.x+x, c.y+y));
					}
		return v;
	}

	/** Pathfinder helper function. */
	private Vector<Coordinate> reconstructPath(
			HashMap<Coordinate, Coordinate> camefrom, Coordinate goal) {
		Vector<Coordinate> coordinates = new Vector<Coordinate>();
		Coordinate c = goal;
		while(camefrom.containsKey(c))
		{
			coordinates.add(c);
			c = camefrom.get(c);
		}
		return coordinates;
	}

	/** Distance between two tiles, in a straight line. */
	Integer estimateCost(Coordinate c1, Coordinate c2) {
		return (int) Math.sqrt(Math.pow(Math.abs(c2.x - c1.x), 2) +
				Math.pow(Math.abs(c2.y - c1.y), 2));
	}

}