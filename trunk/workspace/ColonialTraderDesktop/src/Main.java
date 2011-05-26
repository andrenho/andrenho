import java.awt.BorderLayout;
import javax.swing.JFrame;
import javax.swing.UIManager;


@SuppressWarnings("serial")
public class Main extends JFrame 
{
    private Interface ui;
    
    public Main()
    {
        super("Colonial Trader");
        add(ui = new Interface(), BorderLayout.CENTER);
        pack();
    }

    
	public static void main(String[] args)
	{
        try
        {
            UIManager.setLookAndFeel(UIManager.getSystemLookAndFeelClassName());
        }
        catch (Exception e) { }

		javax.swing.SwingUtilities.invokeLater(new Runnable() 
		{
            public void run() 
            {
                Main m = new Main();
                m.setVisible(true);
            }
        });
	}
	
}
