import java.awt.GridBagConstraints;
import java.awt.GridBagLayout;
import javax.swing.BorderFactory;
import javax.swing.JLabel;
import javax.swing.JPanel;
import javax.swing.SwingConstants;


@SuppressWarnings("serial")
public class Interface extends JPanel
{
    public final CityInfo cityInfo;
    public final Dock dock;


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
        c.gridwidth = 2;
        c.gridheight = 2;
        main.add(buildCargo(), c);

        c.gridheight = c.gridwidth = 0;
        c.gridx = 0;
        c.gridy = 2;
        main.add(buildShipyard(), c);
        
        c.gridx = 1;
        //main.add(new JWorld(captain, world)
        
        c.gridx = 2;
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
        public JLabel repairsNeeded;
        
        Dock()
        {
            setBorder(BorderFactory.createTitledBorder("Dock"));
            
            add(repairsNeeded = new JLabel());
            
        }        
    }

    
    private JPanel buildCargo()
    {
        JPanel ci = new JPanel();
        ci.setBorder(BorderFactory.createTitledBorder("Cargo"));
        
        return ci;
    }

    
    private JPanel buildShipyard()
    {
        JPanel ci = new JPanel();
        ci.setBorder(BorderFactory.createTitledBorder("Shipyard"));
        
        return ci;
    }

    
    private JPanel buildTarget()
    {
        JPanel ci = new JPanel();
        ci.setBorder(BorderFactory.createTitledBorder("Target"));
        
        return ci;
    }
}
