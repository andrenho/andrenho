#ifndef RENDER_TRIANGLE_H_
#define RENDER_TRIANGLE_H_

#include "object.h"

#define GLEW_STATIC
#include <GL/glew.h>

namespace render {

class Triangle : public Object {
public:
    Triangle();

	Triangle(const Triangle&) = delete;
    Triangle& operator=(const Triangle&) = delete;

    const float* Vertices() const { return vertices; }
    int NumVertices() const { return 6; }
    void Setup(unsigned int program);
    glm::vec3 Position() const { return glm::vec3 { 0.0f, 0.0f, 0.0f }; }

private:
    float vertices[6];
};

}

#endif  // RENDER_TRIANGLE_H_

// vim: ts=4:sw=4:sts=4:expandtab
