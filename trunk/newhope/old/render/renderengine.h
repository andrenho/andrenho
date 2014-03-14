#ifndef RENDER_RENDERENGINE_H_
#define RENDER_RENDERENGINE_H_

#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <string>
using namespace std;

#include "render/renderer.h"

namespace render {

class RenderEngine {
public:
    explicit RenderEngine(string window_name);
    ~RenderEngine();

	RenderEngine(const RenderEngine&) = delete;
    RenderEngine& operator=(const RenderEngine&) = delete;

    bool Active() const;
    void ProcessEvents();

    void setRenderer(Renderer* r) { renderer = r; }
    GLuint CompileProgram(string vs_src, string fs_src);

    void Render();

private:
	GLFWwindow* window = nullptr;
    Renderer* renderer = nullptr;

    string ReadWholeFile(string filename);
};

}

#endif  // RENDER_RENDERENGINE_H_

// vim: ts=4:sw=4:sts=4:expandtab
