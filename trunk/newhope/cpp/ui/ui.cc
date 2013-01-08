#include "ui/ui.h"

UI::UI(World const& world)
	: world(world), active(true)
{
}


UI::~UI()
{
}


void 
UI::StartFrame()
{
}


void 
UI::ProcessEvents()
{
	active = false;
}


void 
UI::Draw()
{
}


void 
UI::EndFrame()
{
}
