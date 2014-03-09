#include "render/square.h"

#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
namespace render {

Square::Square()
    : Object(), vertices{
        -0.5f, -0.5f, 0.0f,
         0.5f, -0.5f, 0.0f,
         0.5f,  0.5f, 0.0f,
    }, mvp_id(0)
{
}


void 
Square::Setup(unsigned int program)
{
    GLint posAttrib = glGetAttribLocation(program, "position");
    glVertexAttribPointer(posAttrib, 3, GL_FLOAT, GL_FALSE, 0, 0);
    glEnableVertexAttribArray(posAttrib);

    mvp_id = glGetUniformLocation(program, "MVP");
}

void 
Square::Prepare(glm::mat4 projection, glm::mat4 view)
{
    glm::mat4 model = glm::mat4(1.0f);
    glm::mat4 mvp = projection * view * model;
    glUniformMatrix4fv(mvp_id, 1, GL_FALSE, &mvp[0][0]);
}


}

// vim: ts=4:sw=4:sts=4:expandtab
