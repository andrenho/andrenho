#ifndef RENDER_PYRAMID_H_
#define RENDER_PYRAMID_H_

#include "object.h"

#define GLEW_STATIC
#include <GL/glew.h>

namespace render {

class Pyramid : public Object {
public:
    Pyramid();

	Pyramid(const Pyramid&) = delete;
    Pyramid& operator=(const Pyramid&) = delete;

    const float* Vertices() const { return vertices; }
    int NumVertices() const { return 36; }
    glm::vec3 Position() const { return glm::vec3 { 0.0f, 0.0f, 0.0f }; }

private:
    float vertices[36];
};

}

#endif  // RENDER_TRIANGLE_H_

// vim: ts=4:sw=4:sts=4:expandtab
