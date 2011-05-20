package test;

import java.awt.*;
import javax.swing.*;
import trader.*;

public class Test {

	public static void main(String[] args) {		
		javax.swing.SwingUtilities.invokeLater(new Runnable() {
            public void run() {
        		Captain captain;
        		World world = new World();
        		Travel.travelInterface = new JTravel();
				try {
					captain = Captain.create("John", 5, 5, 5, 5, world);
				} catch (Exception e) {
					e.printStackTrace();
					return;
				}
        		JFrame f = new JFrame("Test");
            	JCity.owner = f;
            	f.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
            	JWorld jworld = new JWorld(captain, world);
            	f.add(new JScrollPane(jworld));
            	f.setPreferredSize(new Dimension(600, 400));
            	f.pack();
            	f.setVisible(true);
            }
        });
		
	}

}
