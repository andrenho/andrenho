#include "ui/ui.h"
#include "util/i18n.h"
#include "util/logger.h"
#include "world/world.h"

Logger logger;

int main(int argc, char** argv)
{
	// initialization
	World world(5000, 5000);
	UI ui(world);

	// main loop
	while(ui.Active())
	{
		ui.StartFrame();
		ui.ProcessEvents();
		ui.Draw();
		ui.EndFrame();
	}

	// free everything
	delete ui;
	delete world;
}
