package trader.world;

import java.util.HashSet;
import java.util.Set;

public class CityNames
{
    /** List of city names already used, to avoid repetition. */
    private static Set<String> namesUsed = new HashSet<String>();
    
    /** Generate random colonial city names. */
    public static String autoGenerate() 
    {
        String[] spanishPrefixF = { "Nueva", "Santa", "De la", "La", "Sierra", "Buena", "Monte" },
                 spanishPrefixM = { "Nuevo", "San", "El", "Del", "Boca", "Bueno", "Monte" },
                 spanishF = { "Alameda", "Angelina", "Atascosa", "Bandera", "Calavera", "Fe",
                              "Esmeralda", "Paz", "Plata", "Madera", "Barbara", "Clara",
                              "Cruz", "Bonita", "Española", "Vista", "Mesa", "Quinta", 
                              "Muerte" },
                 spanishM = { "Amador", "Conejo", "Soto", "Norte", "Dorado", "Hernando",
                              "Monterey", "Sacramento", "Benito", "Diego", "Franscisco",
                              "Juan", "Patricio", "Chico", "Paso", "Gordo", "Indio", 
                              "Gato", "Palacio", "Pueblo", "Antonio", "Marcos", 
                              "Vallejo", "Paraiso" },
                 englishPrefix = { "New", "Saint", "South", "North", "East", "West" },
                 englishPostfix = { "Hill", "River", "Mountain", "Falls", "City", "Valley", "Lake", "Creek", "Junction" },
                 english = { "Ackley", "Albert", "Andover", "Arlington", "Aurora", "Bancroft",
                             "Barnes", "Baxter", "Berkley", "Brooklyn", "Buffalo", "Carlisle",
                             "Carson", "Cedar", "Central", "Clear", "Columbus", "Conway", "Dakota",
                             "Sioux", "Davenport", "Dawson", "Eldora", "Emerson", "Fairbank",
                             "Forest City", "Franklin", "Gilmore", "Halbur", "Hull", "Jackson",
                             "Keosauqua", "Lenox", "McIntire", "Marble", "Missouri", "Sun", "Union",
                             "Nevada", "Providence", "Oakland", "Pacific", "Plainfield", "Radcliffe",
                             "Rose", "Sheffield", "Spring", "Hope", "Titonka", "Volga", "Walker",
                             "Washington", "Webster", "Wyoming", "York" };
        
        String name;
        char type;
        if(Math.random() > 0.5)
        {
            do
            {
                if(Math.random() > 0.5)
                {
                    name = spanishF[(int) (Math.random() * spanishF.length)];
                    type = 'F';
                }
                else
                {
                    name = spanishM[(int) (Math.random() * spanishM.length)];
                    type = 'M';
                }
            } while(namesUsed.contains(name));
            namesUsed.add(name);
            
            if(Math.random() > 0.5)
            {
                if(type == 'F')
                    return spanishPrefixF[(int) (Math.random() * spanishPrefixF.length)] + " " + name;
                else
                    return spanishPrefixM[(int) (Math.random() * spanishPrefixM.length)] + " " + name;
            }
            else
                return name;
        }
        else            
        {
            do
            {
                name = english[(int) (Math.random() * english.length)];
            } while(namesUsed.contains(name));
            namesUsed.add(name);

            if(Math.random() > 0.6)
                return name;
            else if(Math.random() > 0.3)
                return name + " " + englishPostfix[(int) (Math.random() * englishPostfix.length)];
            else
                return englishPrefix[(int) (Math.random() * englishPrefix.length)] + " " + name;
        }
    }

}
