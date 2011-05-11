package crescent;

import java.io.FileNotFoundException;

import crescent.ui.*;
import crescent.util.ConfigFile;
import crescent.util.CrescentException;

public class Game {
	
	// main game singleton variable
	public static Game game = null;
	
	// game elements
	public Map map;
	public Nation[] nations;
	
	// other variables
	public GameOptions gameOptions;
	public ConfigFile configFile;
	public UI ui;
	public boolean running = true;
	
	/** Create a new game. 
	 * @throws CrescentException */
	public static void initialize(UI ui) throws CrescentException
	{
		game = new Game(ui);
		Nation.game = game;
		Map.game = game;
	}
	
	/** Create a new game. Called from initialize. 
	 * @throws CrescentException  */
	private Game(UI ui) throws CrescentException
	{
		try {
			ConfigFile.load("../config.txt");
		} catch (FileNotFoundException e) {
			e.printStackTrace();
			throw new CrescentException(e);
		}
		
		// initialize and ask user for options
		ui.initialize();
		gameOptions = ui.getGameOptions();
		
		// initialize game
		initialize();
		
		// main loop
		while(running)
		{
			// calculate everything
			prepareNewRound();
			
			// every nation plays
			for(Nation n: nations)
				if(n.player)
					ui.playRound(n);
				else
					n.playRoundAI();
			
			running = false;
		}
	}

	/** Initialize a new game. */
	private void initialize() {
		// create map
		map = new Map(gameOptions);
		
		// create nations
		nations = new Nation[gameOptions.nations.size()];
		int i = 0;
		for(GameOptions.GOptNation nat: gameOptions.nations)
			nations[i++] = new Nation(nat);
	}
	
	/** Prepare the game for a new round. */
	private void prepareNewRound() {
		// TODO Auto-generated method stub
	}

}
