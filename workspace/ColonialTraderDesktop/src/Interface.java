import java.awt.Dimension;
import java.awt.GridBagConstraints;
import java.awt.GridBagLayout;
import java.util.HashMap;
import javax.swing.BorderFactory;
import javax.swing.BoxLayout;
import javax.swing.JButton;
import javax.swing.JLabel;
import javax.swing.JPanel;
import javax.swing.JSeparator;
import javax.swing.SwingConstants;
import trader.Good;


@SuppressWarnings("serial")
public class Interface extends JPanel
{
    public final CityInfo cityInfo;
    public final Dock dock;
    public final Cargo cargo;
    public final HashMap<Good, JButton> cargoShip = new HashMap<Good, JButton>();
    public final HashMap<Good, JButton> cargoCity = new HashMap<Good, JButton>();
    public final HashMap<Good, JLabel> priceSell = new HashMap<Good, JLabel>();
    public final HashMap<Good, JLabel> priceBuy = new HashMap<Good, JLabel>();

    public Interface()
    {
        //setLayout(new BorderLayout());
        //JPanel main = new JPanel(new GridBagLayout());
        JPanel main = this;
        main.setLayout(new GridBagLayout());
        
        GridBagConstraints c = new GridBagConstraints();
        c.fill = GridBagConstraints.BOTH;

        c.gridx = c.gridy = 0;
        main.add(cityInfo = new CityInfo(), c);
        
        c.gridy = 1;
        main.add(dock = new Dock(), c);
        
        c.gridx = 1;
        c.gridy = 0;
        main.add(cargo = new Cargo(), c);

        c.gridy = 1;
        c.gridx = 1;
        //main.add(new JWorld(captain, world)
        JPanel tmp = new JPanel();
        tmp.setBorder(BorderFactory.createTitledBorder("World"));
        main.add(tmp, c);
        
        c.gridx = 2;
        c.gridy = 1;
        main.add(buildTarget());
        
        //add(main, BorderLayout.CENTER);
    }

    
    public class CityInfo extends JPanel
    {
        public JLabel cityName, citySize, cityResources, cityType, cityGovernment, cityPirates;
        
        CityInfo()
        {
            setBorder(BorderFactory.createTitledBorder("City Info"));
            setLayout(new GridBagLayout());
            GridBagConstraints c = new GridBagConstraints();
            c.gridx = c.gridy = 0;
            c.fill = GridBagConstraints.BOTH;
            
            add(new JLabel("Name:", SwingConstants.LEFT), c); c.gridy++;
            add(new JLabel("Size:", SwingConstants.LEFT), c); c.gridy++;
            add(new JLabel("Resources:", SwingConstants.LEFT), c); c.gridy++;
            add(new JLabel("Type:", SwingConstants.LEFT), c); c.gridy++;
            add(new JLabel("Government Interference:", SwingConstants.LEFT), c); c.gridy++;
            add(new JLabel("Pirates:", SwingConstants.LEFT), c);
            
            add(cityName = new JLabel());
            add(citySize = new JLabel());
            add(cityResources = new JLabel());
            add(cityType = new JLabel());
            add(cityGovernment = new JLabel());
            add(cityPirates = new JLabel());
        }
    }
    
    public class Dock extends JPanel
    {
        public final JLabel repairsNeeded;
        public final JButton repairButton;
        
        Dock()
        {
            setLayout(new BoxLayout(this, BoxLayout.PAGE_AXIS));
            setBorder(BorderFactory.createTitledBorder("Dock"));
            
            add(repairsNeeded = new JLabel());
            
            repairButton = new JButton("Repair");
            add(repairButton);
            
            JButton buySell = new JButton("Buy/Sell Equipment");
            add(buySell);

            JButton buySellShip = new JButton("Buy/Sell Ship");
            add(buySellShip);
        }        
    }

    
    private class Cargo extends JPanel
    {
        Cargo()
        {
            setBorder(BorderFactory.createTitledBorder("Cargo"));
            
            setLayout(new GridBagLayout());
            GridBagConstraints c = new GridBagConstraints();
            
            // lines
            c.gridx = 1;
            c.gridy = 0;
            c.gridheight = Good.list.length + 2;
            add(new JSeparator(SwingConstants.VERTICAL), c);
            c.gridx = 5;
            add(new JSeparator(SwingConstants.VERTICAL), c);
            c.gridx = 9;
            add(new JSeparator(SwingConstants.VERTICAL), c);
            c.gridx = 0;
            c.gridy = 1;
            c.gridheight = 1;
            c.gridwidth = 12;
            add(new JSeparator(SwingConstants.HORIZONTAL), c);
            
            // titles
            c.gridx = 2;
            c.gridy = 0;
            c.gridwidth = 3;
            add(new JLabel("Sell"), c);
            c.gridx = 6;
            add(new JLabel("Buy"), c);
            c.gridx = 10;
            c.gridwidth = 1;
            add(new JLabel("Price"), c);
            c.gridx++;
            add(new JLabel("+/-"), c);
            c.gridx++;
            add(new JLabel("%"), c);
            
            // data
            c.gridwidth = 1;
            c.gridx = 0;
            c.gridy = 2;
            c.fill = 1;
            for(Good good: Good.list)
            {
                c.gridx = 0;
                add(new JLabel(good.name, SwingConstants.LEFT), c);
                   
                c.gridx = 2;
                JButton cShip = new JButton("0");
                add(cShip, c);
                cargoShip.put(good, cShip);
                
                c.gridx = 3;
                JButton sellAll = new JButton("All");
                add(sellAll, c);
                
                c.gridx = 4;
                JLabel pSell = new JLabel("$ 0");
                add(pSell, c);
                priceSell.put(good, pSell);
                
                c.gridx = 6;
                JButton cCity = new JButton("0");
                add(cCity, c);
                cargoCity.put(good, cCity);
                
                c.gridx = 7;
                JButton buyAll = new JButton("All");
                add(buyAll, c);
                
                c.gridx = 8;
                JLabel pBuy = new JLabel("$ 0");
                add(pBuy, c);
                priceBuy.put(good, pBuy);
                
                c.gridy++;
            }
        }
    }

    
    private JPanel buildTarget()
    {
        JPanel ci = new JPanel();
        ci.setBorder(BorderFactory.createTitledBorder("Target"));
        
        return ci;
    }
}
