#ifndef RENDER_RENDERENGINE_H_
#define RENDER_RENDERENGINE_H_

#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <string>
using namespace std;

namespace render {

class RenderEngine {
public:
    RenderEngine(string window_name);
    ~RenderEngine();

    bool Active();
    void ProcessEvents();
    void Render(class Scene const& scene);
    
    void InstallKeyCallback(GLFWkeyfun cbfun);

    float ScreenRatio() const;

	RenderEngine(const RenderEngine&) = delete;
    RenderEngine& operator=(const RenderEngine&) = delete;

private:
    GLFWwindow* window = nullptr;
};

}

#endif  // RENDER_RENDERENGINE_H_

// vim: ts=4:sw=4:sts=4:expandtab
