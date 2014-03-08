#ifndef RENDER_RENDERER_H_
#define RENDER_RENDERER_H_

#define GLEW_STATIC
#include <GL/glew.h>

#include <vector>
using namespace std;

namespace render {

class Renderer {
public:
    Renderer();
    ~Renderer();

	Renderer(const Renderer&) = delete;
    Renderer& operator=(const Renderer&) = delete;

    void AddObject(class Box* box);

    void Render();

private:
    GLuint vao = 0, prog = 0;
    vector<class Box*> objects = {};
};

}

#endif  // RENDER_RENDERER_H_

// vim: ts=4:sw=4:sts=4:expandtab
