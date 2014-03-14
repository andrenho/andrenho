#ifndef RENDER_RENDERER_H_
#define RENDER_RENDERER_H_

#define GLEW_STATIC
#include <GL/glew.h>
#include <glm/glm.hpp>

#include <vector>
using namespace std;

namespace render {

class Renderer {
public:
    Renderer();
    ~Renderer();

	Renderer(const Renderer&) = delete;
    Renderer& operator=(const Renderer&) = delete;

    void AddObject(class Object* obj);

    void Setup();
    void Render();

    void setCamera(glm::vec3 position, glm::vec3 looking_at) { cam_position = position; cam_lookat = looking_at; }

private:
    GLuint vao = 0, prog = 0;
    vector<class Object*> objects = {};
    glm::vec3 cam_position = { 0.0f, 0.0f, 0.0f };
    glm::vec3 cam_lookat   = { 0.0f, 0.0f, 0.0f };
};

}

#endif  // RENDER_RENDERER_H_

// vim: ts=4:sw=4:sts=4:expandtab
