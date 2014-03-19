#include "render/object.h"

#include "render/camera.h"
#include "render/obj_loader.h"
#include "render/program.h"

namespace render {

Object::Object(string const& origin, Program const& program)
    : program(program)
{
    if(origin.compare(origin.length()-4, 4, ".obj") == 0) {
        OBJ_Loader::Load(origin, *this);
    } else {
        throw "Invalid file extension for file " + origin;
    }
    SetupObject();
}


void 
Object::Render(class Camera const& camera) const
{
    // setup pointers
    glUseProgram(program.Reference());
    glBindVertexArray(vao);

    // send camera info
    SendUniformMatrix("projection", camera.Projection());
    SendUniformMatrix("camera", camera.View());

    // translate, rotate and scale
    glm::mat4 translate = glm::translate(
            glm::mat4(1.0f), 
            glm::vec3(translate_x, translate_y, translate_z));
    glm::mat4 rotate_x = glm::rotate(translate, rotation_x, glm::vec3(1.0f, 0.0f, 0.0f));
    glm::mat4 rotate_y = glm::rotate(rotate_x, rotation_y, glm::vec3(0.0f, 1.0f, 0.0f));
    // TODO - glm::mat4 scale = glm::scale(rotate_y, glm::vec3(scale, scale, scale));
    SendUniformMatrix("model", rotate_y);

    glDrawElements(GL_TRIANGLES, triangles.size() * 3, GL_UNSIGNED_INT, 0);
}


void
Object::SetupObject()
{
    // initialize VAO
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    // initialize VBO
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);

    // upload vertices to graphic card
    int i=0;
    GLfloat* vertex = new GLfloat[vertices.size() * 3];
    for(auto const& vertice: vertices) {
        vertex[i++] = vertice.x;
        vertex[i++] = vertice.y;
        vertex[i++] = vertice.z;
    }
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * 3 * sizeof(GLfloat), vertex, GL_STATIC_DRAW);
    delete[] vertex;

    // create EBO - elements
    glGenBuffers(1, &ebo);
    GLuint* elements = new GLuint[triangles.size() * 3];
    i = 0;
    for(auto const& triangle: triangles) {
        elements[i++] = triangle[0]-1;
        elements[i++] = triangle[1]-1;
        elements[i++] = triangle[2]-1;
    }
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, triangles.size() * 3 * sizeof(GLuint), elements, GL_STATIC_DRAW);
    delete[] elements;

    // link program variables
    GLint vert = glGetAttribLocation(program.Reference(), "vert");
    glVertexAttribPointer(vert, 3, GL_FLOAT, GL_FALSE, 0, nullptr);
    glEnableVertexAttribArray(vert);

    // unbind VBO
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
    
    // TODO - clear mesh
}


void 
Object::SendUniformMatrix(string parameter, glm::mat4 value) const
{
    GLint id = glGetUniformLocation(program.Reference(), parameter.c_str());
    glUniformMatrix4fv(id, 1, GL_FALSE, &value[0][0]);
}


}

// vim: ts=4:sw=4:sts=4:expandtab
