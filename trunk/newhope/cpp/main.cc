#include "libs/sdl/sdl.h"
#include "ui/ui.h"
#include "util/i18n.h"
#include "util/logger.h"
#include "world/world.h"

Logger logger(true, true);

int main(int argc, char** argv)
{
	// initialization
	i18n_init();
	World world(5000, 5000);
	GraphicLibrary* video(new SDL());
	UI* ui(new UI(world, *video));

	// main loop
	while(ui->Active()) {
		ui->StartFrame();
		ui->Draw();
		ui->ProcessEvents();
		world.Process();
		ui->EndFrame();
	}
	
	// clean up
	delete ui;
	delete video;
}
