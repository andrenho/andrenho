#include "render/renderengine.h"
#include "render/scene.h"
#include "render/camera.h"
#include "render/teapot.h"

int main()
{
	RenderEngine engine;

	Camera camera;
	Scene scene(camera);
	Teapot teapot;

	camera.setPosition(4, 4, 3);
	camera.lookAt(0, 0, 0);

	scene.AddObject(teapot);
	scene.setMode(Scene::WIREFRAME);

	while(engine.Active())
	{
		engine.ProcessEvents();
		engine.Render(scene);
	}
}
