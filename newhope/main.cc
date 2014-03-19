#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "render/renderengine.h"
#include "render/scene.h"
#include "render/camera.h"
#include "render/obj_object.h"
#include "render/triangle.h"


float cam_x = 0,
      cam_y = 0,
      cam_z = 30;
render::Scene* s = nullptr;

static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)

int main()
{
    render::RenderEngine engine("newhope");
    engine.InstallKeyCallback(&key_callback);

    render::Camera camera(engine);
    render::Scene scene(camera);
    s = &scene;
    render::OBJ_Object cube("data/teapot.obj");

	camera.LookAt(0, 0, 0);

	//scene.AddObject(triangle);
	scene.AddObject(cube);

    //triangle.Translate(-1, 0, 0);
    //cube.Translate(1, 0, 0);

	while(engine.Active())
	{
        camera.setPosition(cam_x, cam_y, cam_z);
		engine.ProcessEvents();
		engine.Render(scene);
	}
}


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
        case GLFW_KEY_W:
            if(s->Mode() == render::Scene::FILL) {
                s->setMode(render::Scene::WIREFRAME);
            } else {
                s->setMode(render::Scene::FILL);
            }
        default:
            ;
        }
    }
}

// vim: ts=4:sw=4:sts=4:expandtab
