package test;

import java.awt.*;
import java.awt.event.*;
import java.util.HashMap;

import javax.swing.*;

import trader.*;
import trader.Captain.NoGoodsInShipException;
import trader.Captain.NoGoodsInTownException;
import trader.Captain.NoMoneyLeftException;
import trader.Captain.NoSpaceLeftException;

@SuppressWarnings("serial")
public class JCity extends JDialog implements ActionListener {
	
	public static Frame owner = null; 
	private HashMap<Good, JButton> buyButton = new HashMap<Good, JButton>(),
                                  sellButton = new HashMap<Good, JButton>(),
                                  buyMaxButton = new HashMap<Good, JButton>(),
                                  sellMaxButton = new HashMap<Good, JButton>();
	private HashMap<Good, JLabel> priceBuy = new HashMap<Good, JLabel>(),
	                             priceSell = new HashMap<Good, JLabel>();
	private JPanel ipanel;
	private JLabel selfInfo;
	private JButton travel = new JButton("Travel");
	private City city;
	private JTabbedPane tab;
	
	public JCity()
	{
		super(owner, true);
		
		tab = new JTabbedPane();
		add(tab, BorderLayout.PAGE_START);
		
		travel.addActionListener(this);
		
		// info
		ipanel = new JPanel();
		ipanel.setLayout(new BoxLayout(ipanel, BoxLayout.PAGE_AXIS)); 
		tab.addTab("Info", ipanel);
		
		// buy/sell
		JPanel bpanel = new JPanel(new GridBagLayout()),
			   spanel = new JPanel(new GridBagLayout());
		GridBagConstraints c = new GridBagConstraints();
		c.insets = new Insets(5, 10, 5, 10);
		
		int y = 0;
		for(Good good: Good.list)
		{
			c.gridy = y++;

			// amount
			c.gridx = 0;
			JButton bb = new JButton("0");
			buyButton.put(good, bb);
			bpanel.add(bb, c);
			bb.addActionListener(this);
			JButton bs = new JButton("0");
			sellButton.put(good, bs);
			spanel.add(bs, c);
			bs.addActionListener(this);
			
			// name
			c.gridx++;
			bpanel.add(new JLabel(good.name), c);
			spanel.add(new JLabel(good.name), c);

			// max
			c.gridx++;
			bb = new JButton("Max");
			buyMaxButton.put(good, bb);
			bpanel.add(bb, c);
			bb.addActionListener(this);
			bs = new JButton("Max");
			sellMaxButton.put(good, bs);
			spanel.add(bs, c);
			bs.addActionListener(this);

			// price
			c.gridx++;
			priceBuy.put(good, new JLabel("$ 0"));
			bpanel.add(priceBuy.get(good), c);
			priceSell.put(good, new JLabel("$ 0"));
			spanel.add(priceSell.get(good), c);
		}
		
		tab.addTab("Buy", bpanel);
		tab.addTab("Sell", spanel);
		
		selfInfo = new JLabel();
		add(selfInfo, BorderLayout.PAGE_END);
	}

	public void showCity(City city) 
	{
		this.city = city;
		this.setTitle(city.name);
		
		// city info
		ipanel.removeAll();
		ipanel.add(new JLabel("City: " + city.name));
		ipanel.add(new JLabel("System: " + city.politicalSystem.toString()));
		ipanel.add(new JLabel("Type: " + city.type.toString()));
		ipanel.add(new JLabel("Distance: " + city.distanceFrom(Captain.getCaptain().docked)));
		ipanel.add(travel);
		
		if(Captain.getCaptain().docked == city)
		{
			travel.setEnabled(false);
			setAwayCity(false);
		}
		else if(Captain.getCaptain().docked.distanceFrom(city) > Captain.getCaptain().ship.getRange())
		{
			travel.setEnabled(false);
			setAwayCity(true);
		}
		else
		{
			travel.setEnabled(true);
			setAwayCity(true);
		}
		
		// other info
		updateInfo();
		
		pack();
		setVisible(true);
	}

	private void setAwayCity(boolean b) {
		if(b)
		{
			tab.setEnabledAt(1, false);
			tab.setEnabledAt(2, false);
		}
		else
		{
			tab.setEnabledAt(1, true);
			tab.setEnabledAt(2, true);
		}
	}

	private void updateInfo() {
		for(Good good: Good.list)
		{
			buyButton.get(good).setText(Captain.getCaptain().ship.amount.get(good).toString());
			sellButton.get(good).setText(city.amount.get(good).toString());
			priceBuy.get(good).setText("$ " + city.priceBuy(good).toString());
			priceSell.get(good).setText("$ " + city.priceSell(good).toString());
		}
		Ship ship = Captain.getCaptain().ship;
		selfInfo.setText(ship.getSpacesUsed() + "/" + ship.getCapacity() + "    $ " + Captain.getCaptain().doubloons);
	}

	@Override
	public void actionPerformed(ActionEvent e) 
	{
		if(e.getSource().equals(travel))
		{
			Captain.getCaptain().travel(city);
			this.setVisible(false);
			return;
		}
		
		for(Good good: Good.list)
		{
			if(e.getSource().equals(buyButton.get(good)))
				try {
					Captain.getCaptain().buy(good, 1);
				} catch (NoSpaceLeftException e1) {
					JOptionPane.showMessageDialog(this, "No space left on ship.");
					e1.printStackTrace();
				} catch (NoMoneyLeftException e1) {
					JOptionPane.showMessageDialog(this, "Not enough money.");
					e1.printStackTrace();
				} catch (NoGoodsInTownException e1) {
					JOptionPane.showMessageDialog(this, "No goods left on town.");
					e1.printStackTrace();
				}
			else if(e.getSource().equals(sellButton.get(good)))
				try {
					Captain.getCaptain().sell(good, 1);
				} catch (NoGoodsInShipException e1) {
					JOptionPane.showMessageDialog(this, "No goods left on ship.");
					e1.printStackTrace();
				}
			else if(e.getSource().equals(buyMaxButton.get(good)))
				Captain.getCaptain().buyAll(good);
			else if(e.getSource().equals(sellMaxButton.get(good)))
				Captain.getCaptain().sellAll(good);
		}
		updateInfo();
	}

}
