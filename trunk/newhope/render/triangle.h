#ifndef RENDER_TRIANGLE_H_
#define RENDER_TRIANGLE_H_

#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "render/object.h"

namespace render {

class Triangle : public Object {
public:
    Triangle();

    void Render() const;

	Triangle(const Triangle&) = delete;
    Triangle& operator=(const Triangle&) = delete;

private:
    const GLfloat vertex[9] = {
         0.0f,  0.8f, 0.0f,
        -0.8f, -0.8f, 0.0f,
         0.8f, -0.8f, 0.0f
    };
};

}

#endif  // RENDER_TRIANGLE_H_

// vim: ts=4:sw=4:sts=4:expandtab
