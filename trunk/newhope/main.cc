#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

#include <cstdlib>
#include <iostream>
using namespace std;

#include "render/ambientlight.h"
#include "render/camera.h"
#include "render/diffuselight.h"
#include "render/object.h"
#include "render/program.h"
#include "render/renderengine.h"
#include "render/scene.h"

float cam_x = 0,
      cam_y = 3,
      cam_z = 7;
render::Scene* s = nullptr;

static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);

int main()
{
    try {
        render::RenderEngine engine("newhope");
        engine.InstallKeyCallback(&key_callback);

        render::Camera camera(engine);
        render::AmbientLight ambient_light(glm::vec3(1.0f, 1.0f, 1.0f), 0.2f);
        render::Program diffuse_shadow("shaders/vertex.glsl", "shaders/shadow_map_fs.glsl");
        render::DiffuseLight diffuse_light(glm::vec3(1.0f, 1.0f, 1.0f), 0.4f, glm::vec3(-1.0f, -2.0f, -3.0f), diffuse_shadow);

        render::Scene scene(camera);
        scene.AddLight(ambient_light);
        scene.AddLight(diffuse_light);
        s = &scene; // TODO

        render::Program program("shaders/vertex.glsl", "shaders/fragment.glsl");
        render::Object cube("data/torus.obj", program);
        //cube.setSmooth(true);
        render::Object ground("data/ground.obj", program);

        camera.LookAt(0, 0, 0);

        scene.AddObject(cube);
        scene.AddObject(ground);

        while(engine.Active())
        {
            camera.setPosition(cam_x, cam_y, cam_z);
            engine.ProcessEvents();
            engine.Render(scene);
        }

    } catch(const char*& err) {
        cout << err << endl;
        std::abort();
    } catch(string& err) {
        cout << err << endl;
        std::abort();
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
            cam_x -= 1; break;
        case GLFW_KEY_RIGHT:
            cam_x += 1; break;
        case GLFW_KEY_UP:
            cam_y += 1; break;
        case GLFW_KEY_DOWN:
            cam_y -= 1; break;
        case GLFW_KEY_COMMA:
            cam_z += 1; break;
        case GLFW_KEY_PERIOD:
            cam_z -= 1; break;
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
