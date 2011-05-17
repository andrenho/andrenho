package test;

import java.awt.*;
import javax.swing.*;
import trader.*;

public class Test {

	public static void main(String[] args) {		
		javax.swing.SwingUtilities.invokeLater(new Runnable() {
            public void run() {
        		Captain captain = new Captain("John", 5, 5, 5, 5);
        		World world = new World();
        		captain.world = world;
        		captain.docked = world.cities.get(0);
            	JFrame f = new JFrame("Test");
            	JWorld jworld = new JWorld(captain, world);
            	f.add(new JScrollPane(jworld));
            	f.setPreferredSize(new Dimension(640, 480));
            	f.pack();
            	f.setVisible(true);
            }
        });
		
	}

}
