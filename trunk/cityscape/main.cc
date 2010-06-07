#include "dbggui.h"

int main(int argc, char** argv)
{
	(void)argc;
	(void)argv;

	GUI* gui = new DebugGUI(new City("Andreville", 15, 15));
	gui->Startup();
	gui->Main();
	return 0;
}
