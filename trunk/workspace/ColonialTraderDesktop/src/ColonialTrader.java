import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.HashMap;
import trader.Captain;
import trader.City;
import trader.Good;
import trader.World;

public class ColonialTrader
{
    private static Captain captain;
    private static World world;

    public static void main(String[] args) throws Exception
    {
        world = new World();
        captain = createCaptain(world);
        
        while(cityMenu())
            ;
    }

    private static Captain createCaptain(World w) throws Exception 
    {
        return Captain.create("Test", 5, 5, 5, 5, w);
    }

    private static boolean cityMenu()
    {
        println();
        City city = captain.getDocked();
        println("City: " + city.name + 
                " (" + city.terrain.toString().toLowerCase() + 
                "/" + city.type.toString().toLowerCase() + ")");
        println("  [I]nformation");
        println("  [C]hart");
        println("  [W]arehouse");
        println("  [Q]uit");
        print("? ");
        
        switch(inputc())
        {
            case 'i':
                informationMenu();
                break;
            case 'c':
                chart();
                break;
            case 'w':
                warehouse();
                break;
            case 'q':
                return false;
        }
        return true;
    }

    private static void informationMenu()
    {
        // TODO Auto-generated method stub
        
    }

    private static void chart()
    {
        println();
        println("Traveling destinations:");
        
        char i = 'a';
        HashMap<Character, City> cities = new HashMap<Character, City>();
        for(City destination: captain.availableCities.keySet())
        {
            println("  [" + i + "] " + destination.name);
            cities.put(i, destination);
            i++;
        }
        print("? ");
        
        char c = inputc();
        if(cities.containsKey(c))
            captain.travel(cities.get(c));
    }

    private static void warehouse()
    {
        int maxchars = 0;
        
        for(Good g: Good.list)
            maxchars = g.name.length();
        
        char i = 'a';
        for(Good g: Good.list)
        {
            print("[" + i + "] ");
            print(g.name);
            for(int j=0; j<(maxchars - g.name.length()); j++)
                print(" ");
            
        }
    }

    private static void print(String s)
    {
        System.out.print(s);
    }

    private static void println()
    {
        System.out.println("");
    }
    
    private static void println(String s)
    {
        System.out.println(s);
    }
    
    private static char inputc()
    {
        BufferedReader lineOfText = new BufferedReader(new InputStreamReader(System.in));
        try
        {
            return (char) lineOfText.read();
        }
        catch (IOException e)
        {
            e.printStackTrace();
            return 0;
        }
    }
    
    private static String input()
    {
        BufferedReader lineOfText = new BufferedReader(new InputStreamReader(System.in));
        try
        {
            String textLine = lineOfText.readLine();
            return textLine;
        }
        catch (IOException e)
        {
            e.printStackTrace();
            return "";
        }
    }
    
    private static int inputInt()
    {
        return Integer.parseInt(input());
    }
}
