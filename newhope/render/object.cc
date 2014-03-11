#include "render/object.h"

namespace render {

Object::Object()
{
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
}


void
Object::UploadToGPU()
{
    glBufferData(GL_ARRAY_BUFFER, NumVertices() * sizeof(float), Vertices(), GL_STATIC_DRAW);
}


void 
Object::Setup(unsigned int program)
{
    GLint posAttrib = glGetAttribLocation(program, "position");
    glVertexAttribPointer(posAttrib, 3, GL_FLOAT, GL_FALSE, 0, 0);
    glEnableVertexAttribArray(posAttrib);

    mvp_id = glGetUniformLocation(program, "MVP");
}


void 
Object::Prepare(glm::mat4 projection, glm::mat4 view)
{
    glm::mat4 model = ModelMatrix();
    glm::mat4 mvp = projection * view * model;
    glUniformMatrix4fv(mvp_id, 1, GL_FALSE, &mvp[0][0]);
}


glm::mat4
Object::ModelMatrix() const
{
    return glm::mat4(1.0f);
}

}

// vim: ts=4:sw=4:sts=4:expandtab
