#include "render/triangle.h"

namespace render {

Triangle::Triangle()
    : Object(), vertices{
         0.0f,  0.5f, // Vertex 1 (X, Y)
         0.5f, -0.5f, // Vertex 2 (X, Y)
        -0.5f, -0.5f  // Vertex 3 (X, Y)
    }
{
}


void 
Triangle::Setup(unsigned int program)
{
    GLint posAttrib = glGetAttribLocation(program, "position");
    glVertexAttribPointer(posAttrib, 2, GL_FLOAT, GL_FALSE, 0, 0);
    glEnableVertexAttribArray(posAttrib);
}

}

// vim: ts=4:sw=4:sts=4:expandtab
