package crescent.ui;

import java.util.Vector;

public class GameOptions {
	public int map_w, map_h;
	public Vector<GOptNation> nations = new Vector<GOptNation>();
	
	public class GOptNation {
		public boolean player;
	}
}
