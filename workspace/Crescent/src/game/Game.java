package game;

public class Game {

	public Tile[][] tile;
	
	public Game(int w, int h)
	{
		tile = new Tile[w][h];
		for(int x=0; x<w; x++)
			for(int y=0; y<h; y++)
				tile[x][y] = new Tile(Terrain.OCEAN);
	}
}
