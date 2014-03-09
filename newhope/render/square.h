#ifndef RENDER_SQUARE_H_
#define RENDER_SQUARE_H_

#include "object.h"

#define GLEW_STATIC
#include <GL/glew.h>

namespace render {

class Square : public Object {
public:
    Square();

	Square(const Square&) = delete;
    Square& operator=(const Square&) = delete;

    const float* Vertices() const { return vertices; }
    int NumVertices() const { return 9; }
    glm::vec3 Position() const { return glm::vec3 { 0.0f, 0.0f, 0.0f }; }

    void Setup(unsigned int program);
    void Prepare(glm::mat4 projection, glm::mat4 view);

private:
    float vertices[9];
    GLuint mvp_id;
};

}

#endif  // RENDER_TRIANGLE_H_

// vim: ts=4:sw=4:sts=4:expandtab
