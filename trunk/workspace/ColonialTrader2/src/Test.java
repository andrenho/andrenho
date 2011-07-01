import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.HashMap;
import trader.Game;
import trader.people.Captain;
import trader.people.Skills;
import trader.world.City;
import trader.world.Travel;


public class Test
{
    public static void main(String args[])
    {
        Skills skills = new Skills(5, 5, 5, 5);
        Captain captain = new Captain("Teste", skills);
        Game game = new Game(captain);
        
        cityMenu(game);
    }
    
    private static void cityMenu(Game game)
    {
        while(true)
        {
            City currentCity = game.captain.ship.cityDocked;
            println("City: " + currentCity.name + " (" + currentCity.coord.x + "," + currentCity.coord.y +  ")");
            println("[C]ities in range");
            println("[Q]uit");
            print("? ");
        
            switch(inputc())
            {
                case 'c':
                    listCities(game);
                    break;
                case 'q':
                    return;
            }
        }
    }

    private static void listCities(Game game)
    {
        while(true)
        {
            HashMap<City, Integer> cities = 
                game.captain.ship.cityDocked.citiesInRange(
                        game.world, game.captain.ship.getRange());
            char ch = 'a';
            for(Object city: cities.keySet().toArray())
                println("[" + (ch++) + "] " + ((City)city).name  + " (" + cities.get(city) + ")");
            println("[r] Return to Main Menu");
            
            print("? ");
        
            char c = inputc();
            if(c == 'r')
                return;
            else if(c >= 'a' && c < ch)
                foreignCityMenu(game, (City)cities.keySet().toArray()[c - 'a']);
        }
    }

    
    private static void foreignCityMenu(Game game, City city)
    {
        while(true)
        {
            println(city.name);
            println("[T]ravel");
            println("[R]eturn");
            
            char c = inputc();
            if(c == 'r')
                return;
            else if(c == 't')
            {
                Travel travel = new Travel(city);
                travelMenu(game, travel);
            }
        }
    }

    private static void travelMenu(Game game, Travel travel)
    {
        
    }

    private static void print(String s)
    {
        System.out.print(s);
    }
    @SuppressWarnings("unused")
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
    @SuppressWarnings("unused")
    private static int inputInt()
    {
        return Integer.parseInt(input());
    }

}
