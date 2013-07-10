package crescent.util;

import java.io.File;
import java.io.FileNotFoundException;
import java.util.Scanner;

public class ConfigFile 
{
	public static void load(String string) throws FileNotFoundException 
	{
		Scanner sc = new Scanner(new File(string));
		while(sc.hasNext())
		{
			
		}
	}
}
