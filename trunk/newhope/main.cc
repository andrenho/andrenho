#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "render/renderengine.h"
#include "render/scene.h"
#include "render/camera.h"
#include "render/triangle.h"


float cam_x = 0,
      cam_y = 0,
      cam_z = 3;


static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    (void) scancode;
    (void) mods;

    if(action == GLFW_PRESS) {
        switch(key)
        {
        case GLFW_KEY_ESCAPE:
            glfwSetWindowShouldClose(window, GL_TRUE);
            break;
        case GLFW_KEY_LEFT:
            cam_x -= 0.3f; break;
        case GLFW_KEY_RIGHT:
            cam_x += 0.3f; break;
        case GLFW_KEY_UP:
            cam_y += 0.3f; break;
        case GLFW_KEY_DOWN:
            cam_y -= 0.3f; break;
        case GLFW_KEY_COMMA:
            cam_z += 0.3f; break;
        case GLFW_KEY_PERIOD:
            cam_z -= 0.3f; break;
        default:
            ;
        }
    }
}


int main()
{
    render::RenderEngine engine("newhope");
    engine.InstallKeyCallback(&key_callback);

    render::Camera camera(engine);
    render::Scene scene(camera);
    render::Triangle object1, object2;

	camera.LookAt(0, 0, 0);

	scene.AddObject(object1);
	scene.AddObject(object2);
	scene.setMode(render::Scene::WIREFRAME);

    object1.Translate(-1, 0, 0);
    object2.Translate(1, 0, 0);

	while(engine.Active())
	{
        camera.setPosition(cam_x, cam_y, cam_z);
		engine.ProcessEvents();
		engine.Render(scene);
	}
}

// vim: ts=4:sw=4:sts=4:expandtab
