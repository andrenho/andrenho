package crescent.test;

import javax.swing.JFrame;

import crescent.Game;
import crescent.Nation;
import crescent.ui.GameOptions;
import crescent.ui.GameOptions.GOptNation;
import crescent.ui.UI;
import crescent.util.CrescentException;

@SuppressWarnings("serial")
public class TestUI extends JFrame implements UI {
	
	public static void main(String[] args)
	{
		try {
			Game.initialize(new TestUI());
		} catch (CrescentException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
	}

	@Override
	public void initialize() {
		// TODO Auto-generated method stub
		
	}

	@Override
	public GameOptions getGameOptions() {
		GameOptions gcfg = new GameOptions();
		gcfg.map_h = 20;
		gcfg.map_w = 20;
		
		GOptNation nation = gcfg.new GOptNation();
		nation.player = true;
		gcfg.nations.add(nation);
		
		return gcfg;
	}

	@Override
	public void playRound(Nation n) {
		// TODO Auto-generated method stub
		
	}

}
