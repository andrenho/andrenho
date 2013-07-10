package crescent;

import crescent.ui.GameOptions;

public class Map {
	
	static Game game;
	public Tile[][] tiles;
	
	public Map(GameOptions gcfg)
	{
		// create map
		tiles = new Tile[gcfg.map_w][gcfg.map_h];
		
		for(int x=0; x<gcfg.map_w; x++)
			for(int y=0; y<gcfg.map_h; y++)
				tiles[x][y] = new Tile();
	}
	
}
