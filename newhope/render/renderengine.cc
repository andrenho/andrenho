#include "render/renderengine.h"

#include <cassert>
#include <iostream>
using namespace std;

#include "render/scene.h"

namespace render {

RenderEngine::RenderEngine(string window_name)
{
	// initalize GLFW
	glfwInit();

	// create hints for OpenGL
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	
	// create window
	window = glfwCreateWindow(800, 600, window_name.c_str(), nullptr, nullptr);
    assert(window);

	// make OpenGL context active
	glfwMakeContextCurrent(window);

	// GLEW
	glewExperimental = GL_TRUE;
	glewInit();

    // setup OpenGL
    glClearColor(0, 0, 0, 1);
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);
    glEnable(GL_CULL_FACE);

    // clear error queue
    while(glGetError() != GL_NO_ERROR);
}


RenderEngine::~RenderEngine()
{
	// terminate GLFW
    glfwDestroyWindow(window);
	glfwTerminate();
}


bool 
RenderEngine::Active()
{
    return !glfwWindowShouldClose(window);
}


void 
RenderEngine::ProcessEvents()
{
    glfwPollEvents();
}


void 
RenderEngine::Render(Scene const& scene)
{
    scene.Render();
    glfwSwapBuffers(window);
}


void 
RenderEngine::InstallKeyCallback(GLFWkeyfun cbfun)
{
    glfwSetKeyCallback(window, cbfun);
}


void 
RenderEngine::WindowSize(int& w, int& h) const
{
    glfwGetFramebufferSize(window, &w, &h);
}


float 
RenderEngine::ScreenRatio() const
{
    //int width, height;
    //glfwGetFramebufferSize(window, &width, &height);
    return 4.0f / 3.0f;
    //return static_cast<float>(width) / static_cast<float>(height);
}


}

// vim: ts=4:sw=4:sts=4:expandtab
