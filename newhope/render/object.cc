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

    // send camera info
    SendUniform("projection", camera.Projection());
    SendUniform("camera", camera.View());

    // translate, rotate and scale
    glm::mat4 translate = glm::translate(
            glm::mat4(1.0f), 
            glm::vec3(translate_x, translate_y, translate_z));
    glm::mat4 rotate_x = glm::rotate(translate, rotation_x, glm::vec3(1.0f, 0.0f, 0.0f));
    glm::mat4 rotate_y = glm::rotate(rotate_x, rotation_y, glm::vec3(0.0f, 1.0f, 0.0f));
    // TODO - glm::mat4 scale = glm::scale(rotate_y, glm::vec3(scale, scale, scale));
    SendUniform("model", rotate_y);

    // send lights
    SendUniform("dir_light.color", glm::vec3{ 1.0f, 1.0f, 0.0f });
    SendUniform("dir_light.intensity", 0.3f);

    glBindVertexArray(vao);
    glDrawElements(GL_TRIANGLES, triangles.size() * 3, GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
}


void
Object::SetupObject()
{
    // initialize VAO
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    // upload data
    UploadVertices(vertices, vbo);
    UploadVertices(normal_vertices, vbo_normals);
    UploadElements(triangles, ebo);
    UploadElements(normals, ebo_normals);

    // link GPU data to vertex shader variables
    LinkVertexArray("vert", vbo, ebo);
    LinkVertexArray("normals", vbo_normals, ebo_normals);

    // unbind VAO & VBO
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    // TODO - clear mesh
}


void
Object::UploadVertices(vector<glm::vec3> const& vertices, GLuint& vbo)
{
    // VBO - upload vertices to GPU
    int i=0;
    GLfloat* vertex = new GLfloat[vertices.size() * 3];
    for(auto const& vertice: vertices) {
        vertex[i++] = vertice.x;
        vertex[i++] = vertice.y;
        vertex[i++] = vertice.z;
    }
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * 3 * sizeof(GLfloat), vertex, GL_STATIC_DRAW);
    delete[] vertex;
}


void
Object::UploadElements(vector<array<int,3>> const& elements, GLuint& ebo)
{
    // EBO - upload elements to GPU
    GLuint* el = new GLuint[elements.size() * 3];
    int i = 0;
    for(auto const& element: elements) {
        el[i++] = element[0]-1;
        el[i++] = element[1]-1;
        el[i++] = element[2]-1;
    }
    glGenBuffers(1, &ebo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, elements.size() * 3 * sizeof(GLuint), el, GL_STATIC_DRAW);
    delete[] el;
}


void
Object::LinkVertexArray(string const& variable, GLuint vbo, GLuint ebo)
{
    // link program variables
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
    GLint variable_id = glGetAttribLocation(program.Reference(), variable.c_str());
    glVertexAttribPointer(variable_id, 3, GL_FLOAT, GL_FALSE, 0, nullptr);
    glEnableVertexAttribArray(variable_id);
}


// ------ send uniforms


void 
Object::SendUniform(string parameter, glm::mat4 value) const
{
    GLint id = glGetUniformLocation(program.Reference(), parameter.c_str());
    glUniformMatrix4fv(id, 1, GL_FALSE, &value[0][0]);
}


void 
Object::SendUniform(string parameter, glm::vec3 value) const
{
    GLint id = glGetUniformLocation(program.Reference(), parameter.c_str());
    glUniform3fv(id, 1, &value[0]);
}


void 
Object::SendUniform(string parameter, float value) const
{
    GLint id = glGetUniformLocation(program.Reference(), parameter.c_str());
    glUniform1f(id, value);
}


}

// vim: ts=4:sw=4:sts=4:expandtab
