module config.config;

import std.stdio;
import std.stream;
import std.string;


alias string[string] ConfigNode;
alias ConfigNode[][string] Config;


private
{
	enum Type { EOF, EOL, VALUE, TITLE };

	char c;
	string token;
	bool category;
	Stream f;
	Type type;
	int line = 1;
	
	void skipSpaces()
	{
		if(c == '#')
			while((c = f.getc()) != '\n') { }
		else
			while(c == ' ' || c == '\t')
				c = f.getc();
	}
	
	void next()
	{
		skipSpaces();
		
		if(f.eof())
		{
			token = "";
			type = Type.EOF;
		}
		else if(c == '\n' || c == '\r')
		{
			token = "\n";
			do
			{
				c = f.getc();
			} while(c == '\n' || c == '\r');
			type = Type.EOL;
			line++;
		}
		else if(c == '[')
		{
			token = "";
			while((c = f.getc()) != ']')
				token ~= c;
			c = f.getc();
			type = Type.TITLE;
		}
		else if(c == '\'')
		{
			token = "";
			while((c = f.getc()) != '\'')
				token ~= c;
			c = f.getc();
			type = Type.VALUE;
		}
		else
		{
			token = "";
			do
			{
				token ~= c;
				c = f.getc();
			} while(c != '\n' && c != ' ' && c != '\t' && c != '#' && !f.eof());
			type = Type.VALUE;
		}
	}
	
	void expected(string s)
	{
		throw new Exception(format("Expected %s in line %d.", s, line));
	}
}


Config readConfigFile(string file)
{
	Config config;
	
	f = new BufferedFile(file, FileMode.In);
	c = f.getc();
	
	next();

	while(type != Type.EOF)
	{
		// get title
		if(type != Type.TITLE)
			expected("title");
		string title = token;
		next();
		if(type != Type.EOL)
			expected("EOL");
		next();
		
		ConfigNode[] cns;
		
		// get headers
		string[]  headers;
		while(type != Type.EOL)
		{
			if(type != Type.VALUE)
				expected("value");
			headers ~= token;
			next();
		}
		next();
		
		// get values
		uint i;
		while(type != Type.EOL && type != Type.EOF)
		{
			if(type == Type.TITLE)
				break;

			ConfigNode cn;
			i = 0;
			do
			{
				cn[headers[i]] = token;
				next();
				i++;
			} while(type == Type.VALUE);
			cns ~= cn;
			
			if(type != Type.EOL && type != Type.EOF)
				expected("EOL or EOF");
			next();
		}

		config[title] = cns;
	}
	
	return config;
}