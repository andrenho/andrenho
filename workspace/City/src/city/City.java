package city;

import java.util.Vector;

public class City {

	public Vector<Person> people;
	
	public City()
	{
		people = new Vector<Person>();
		addImmigrant();
	}

	private void addImmigrant() {
		Person p = new Person();
		people.add(p);
	}

	public void tick() {
		for(Person p: people)
			p.tick();
	}
	
}
