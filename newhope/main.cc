#include "render/renderengine.h"
#include "render/scene.h"
#include "render/camera.h"
#include "render/triangle.h"

int main()
{
    render::RenderEngine engine("newhope");

    render::Camera camera;
    render::Scene scene(camera);
    render::Triangle object;

	camera.setPosition(4, 4, 3);
	camera.LookAt(0, 0, 0);

	scene.AddObject(object);
	scene.setMode(render::Scene::WIREFRAME);

	while(engine.Active())
	{
		engine.ProcessEvents();
		engine.Render(scene);
	}
}

// vim: ts=4:sw=4:sts=4:expandtab
