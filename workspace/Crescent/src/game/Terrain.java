package game;

import java.util.Vector;

public class Terrain {
	
	public static Vector<Terrain> all = new Vector<Terrain>();
	public String name;
	public int overlay;
	public int costToEnter;
	public Terrain switchStatus;
	
	public Terrain(String name, int overlay, int costToEnter, int defensiveBonus,
			int[] productivity, Terrain switchStatus)
	{
		this.name = name;
		this.overlay = overlay;
		this.costToEnter = costToEnter;
		this.switchStatus = switchStatus;
		all.add(this);
	}
	
	public static Terrain TUNDRA   = new Terrain("Tundra",          1, 0, 0, new int[] { 2, 0, 0, 0, 0, 2, 2, 1, 0 }, null);
	public static Terrain DESERT   = new Terrain("Desert",         13, 1, 0, new int[] { 1, 0, 0, 2, 0, 1, 3, 2, 0 }, null);
	public static Terrain PLAINS   = new Terrain("Planis",         14, 1, 0, new int[] { 4, 2, 1, 0, 0, 1, 1, 0, 0 }, null);
	public static Terrain PRAIRIE  = new Terrain("Prairie",        15, 1, 0, new int[] { 3, 3, 0, 0, 0, 0, 0, 0, 0 }, null);
	public static Terrain STEPPE   = new Terrain("Steppe",         16, 1, 0, new int[] { 2, 2, 3, 0, 0, 0, 0, 0, 0 }, null);
	public static Terrain MARSH    = new Terrain("Marsh",          17, 2, 1, new int[] { 3, 1, 2, 0, 0, 2, 4, 2, 0 }, null);

	public static Terrain BOREAL_F = new Terrain("Boreal forest",   6, 2, 2, new int[] { 1, 0, 0, 0, 2, 1, 1, 1, 0 }, TUNDRA);
	public static Terrain SCRUB    = new Terrain("Scrubland",       7, 1, 2, new int[] { 1, 0, 0, 4, 1, 1, 2, 1, 0 }, DESERT);
	public static Terrain MIXED_F  = new Terrain("Mixed forest",    8, 2, 2, new int[] { 2, 1, 0, 0, 3, 0, 1, 0, 0 }, PLAINS);
	public static Terrain SAVANNAH = new Terrain("Savannah",        9, 1, 1, new int[] { 1, 1, 0, 0, 2, 0, 1, 0, 0 }, PRAIRIE);
	public static Terrain WOODLAND = new Terrain("Woodland",       10, 2, 2, new int[] { 1, 0, 1, 0, 2, 0, 1, 0, 0 }, STEPPE);
	public static Terrain SWAMP    = new Terrain("Swamp",          11, 3, 3, new int[] { 2, 0, 0, 0, 1, 1, 3, 2, 0 }, MARSH);

	public static Terrain ARCTIC   = new Terrain("Arctic",          5, 2, 0, new int[] { 0, 0, 0, 0, 0, 1, 0, 1, 1 }, null);
	public static Terrain SEA      = new Terrain("Sea",             2, 1, 0, new int[] { 3, 0, 0, 0, 0, 0, 0, 0, 0 }, null);
	public static Terrain OCEAN    = new Terrain("Ocean",           1, 1, 0, new int[] { 3, 0, 0, 0, 0, 0, 0, 0, 0 }, null);
	public static Terrain HILLS    = new Terrain("Hills",           4, 2, 4, new int[] { 1, 0, 0, 0, 0, 3, 0, 3, 0 }, null);
	public static Terrain MOUNTAIN = new Terrain("Mountains",       3, 3, 6, new int[] { 0, 0, 0, 0, 0, 3, 0, 3, 1 }, null);
	
}
