using namespace std;

int main()
{
	Options options;
	Screen screen;
	Terminal terminal(options, screen);

	while(1)
	{
		screen.BeginFrame();
		screen.Update();

		for(vector<Filter>::const_iterator filter = options.Filters().begin(); 
				filter < options.Filters().end(); filter++)
			terminal.ApplyFilter(*filter);

		terminal.UpdateToScreen();

		screen.EndFrame();
	}
}
