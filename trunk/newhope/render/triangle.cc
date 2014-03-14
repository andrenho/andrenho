#include "render/triangle.h"

#include <iostream>
using namespace std;

namespace render {

Triangle::Triangle()
{
    // setup program
    program = SetupProgram("shaders/vertex.glsl", "shaders/fragment.glsl");

    // initialize VAO
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    // initialize VBO
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);

    // upload data to graphic card
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertex), vertex, GL_STATIC_DRAW);

    // link program variables
    GLint position = glGetAttribLocation(program, "position");
    glVertexAttribPointer(position, 3, GL_FLOAT, GL_FALSE, 0, nullptr);
    glEnableVertexAttribArray(position);

    // unbind VBO
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}


void 
Triangle::Render() const
{
    glDrawArrays(GL_TRIANGLES, 0, 3);
}


}

// vim: ts=4:sw=4:sts=4:expandtab
