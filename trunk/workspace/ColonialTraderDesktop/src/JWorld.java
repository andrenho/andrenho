
 
import java.awt.Color;
import java.awt.Graphics;
import java.awt.Graphics2D;
import java.awt.Rectangle;
import java.awt.event.MouseEvent;
import java.awt.event.MouseListener;
import javax.swing.JPanel;
import test.JCity;
import trader.Captain;
import trader.City;
import trader.World;

@SuppressWarnings("serial")
public class JWorld extends JPanel implements MouseListener {

        private final World world;
        private final Captain captain;
        private JCity jcity;

        public JWorld(Captain captain, World world) {
                this.world = world;
                this.captain = captain;
                this.jcity = new JCity();
                addMouseListener(this);
        }

        @Override
        public void paint(Graphics g)
        {
                super.paint(g);
                setBackground(Color.WHITE);

                Graphics2D g2d = (Graphics2D)g;

                g2d.setPaint(Color.white);
                for(int x=0; x<World.w; x++)
                        for(int y=0; y<World.h; y++)
                                if(world.land[x][y])
                                        g2d.fill(new Rectangle(x * 4, y * 4, 4, 4));

                for(City city: world.cities)
                {
                        if(city == Captain.getCaptain().getDocked())
                                g2d.setPaint(Color.blue);
                        else if(Captain.getCaptain().availableCities.containsKey(city))
                                g2d.setPaint(Color.red);
                        else
                                g2d.setPaint(Color.black);
                        g2d.drawRect((int)city.coordinates.x * 4, (int)city.coordinates.y * 4, 4, 4);
                }
        }

        @Override
        public void mouseClicked(MouseEvent e)
        {
                for(City city: world.cities)
                        if(e.getX() >= (int)city.coordinates.x * 4 - 8 && e.getX() < (int)city.coordinates.x * 4 + 8
                        && e.getY() >= (int)city.coordinates.y * 4 - 8 && e.getY() < (int)city.coordinates.y * 4 + 8)
                        {
                                jcity.showCity(city);
                                repaint();
                                break;
                        }
        }

        public void mouseEntered(MouseEvent arg0)  { }
        public void mouseExited(MouseEvent arg0)   { }
        public void mousePressed(MouseEvent arg0)  { }
        public void mouseReleased(MouseEvent arg0) { }

}
