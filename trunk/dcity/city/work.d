module city.work;

import city.structures;
import city.person;

class Job
{
	uint minGrade;
	uint salary;
	Person worker;
	
	this(uint minGrade, uint salary)
	{
		this.minGrade = minGrade;
		this.salary = salary;
		this.worker = null;
	}
}


abstract class Workplace : Structure
{
	Job[] jobs;
	

    this(uint x, uint y) { super(x, y); }


	bool applyForJob(Person person)
	{
		foreach(Job job; jobs)
			if(job.worker is null && person.grade >= job.minGrade)
			{
				takeJob(job, person);
				return true;
			}
		return false;
	}
	
	
	void takeJob(Job job, Person person)
	{
		job.worker = person;
		person.job = job;
		person.workplace = this;
	}
	
	
	uint workers()
	{
		int c = 0;
		foreach(Job job; jobs)
			if(job.worker !is null)
				c++;
		return c;
	}
}


abstract class Industry : Workplace
{
    this(uint x, uint y) { super(x, y); }
}