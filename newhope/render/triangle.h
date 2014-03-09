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
    int VerticesSize() const { return 6; }
    int NumVertices() const { return 3; }
    void UploadToGPU(unsigned int program);

private:
    float vertices[6];
};

}

#endif  // RENDER_TRIANGLE_H_

// vim: ts=4:sw=4:sts=4:expandtab
