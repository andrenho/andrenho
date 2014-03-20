#include "render/object.h"

#include <iostream>
using namespace std;

#include "render/camera.h"
#include "render/light.h"
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
    cout << "Object " << origin << " loaded with " << vertices.size() << " vertices, " << triangles.size() << " triangles, "
         << normal_vertices.size() << " normal vertices, and " << normals.size() << " normals." << endl;
}


void 
Object::Render(class Camera const& camera, vector<Light const*> const& lights) const
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

    // flat/smooth
    SendUniform("smooth_model", true);

    // apply lights
    ApplyLights(lights);

    // draw elements
    glBindVertexArray(vao);
    glDrawElements(GL_TRIANGLES, triangles.size() * 3, GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
}


void
Object::DebugVertices() const
{
    for(auto const& triangle: triangles) {
        cout << "[ ";
        for(int i=0; i<3; i++) {
             cout << "(" 
                  << vertices[triangle[i]-1].x << ", "
                  << vertices[triangle[i]-1].y << ", "
                  << vertices[triangle[i]-1].z << ") ";
        }
        cout << "]" << endl;
    }
}


void
Object::SetupObject()
{
    // initialize VAO
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    // upload data
    UploadVertices(vertices, vbo);
    UploadElements(triangles, ebo);
    UploadVertices(normal_vertices, vbo_normals);
    UploadElements(normals, ebo_normals);
    //UploadNormals(normal_vertices, normals, vbo_normals);

    // link GPU data to vertex shader variables
    LinkVertexArray("normals", vbo_normals, ebo_normals);
    LinkVertexArray("vert", vbo, ebo);

    // unbind VAO & VBO
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    // TODO - clear mesh
}


void
Object::UploadVertices(vector<glm::vec3> const& vertices, GLuint& vbo)
{
    // VBO - upload vertices to GPU
    vector<GLfloat> vertex;
    for(auto const& vertice: vertices) {
        vertex.push_back(vertice.x);
        vertex.push_back(vertice.y);
        vertex.push_back(vertice.z);
    }
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, vertex.size() * sizeof(GLfloat), &vertex[0], GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}


void
Object::UploadElements(vector<array<int,3>> const& elements, GLuint& ebo)
{
    // EBO - upload elements to GPU
    vector<GLuint> el;
    for(auto const& element: elements) {
        el.push_back(element[0]-1);
        el.push_back(element[1]-1);
        el.push_back(element[2]-1);
    }
    glGenBuffers(1, &ebo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, el.size() * sizeof(GLuint), &el[0], GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}


void
Object::UploadNormals(vector<glm::vec3> const& vertices, vector<array<int,3>> const& elements, GLuint& vbo)
{
    vector<GLfloat> vertex;
    for(auto const& element: elements) {
        for(int i=0; i<3; i++) {
            vertex.push_back(vertices[element[i]-1].x);
            vertex.push_back(vertices[element[i]-1].y);
            vertex.push_back(vertices[element[i]-1].z);
        }
    }
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, vertex.size() * sizeof(GLfloat), &vertex[0], GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}


void
Object::LinkVertexArray(string const& variable, GLuint vbo, GLuint ebo)
{
    // link program variables
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
    GLint variable_id = glGetAttribLocation(program.Reference(), variable.c_str());
    glEnableVertexAttribArray(variable_id);
    glVertexAttribPointer(variable_id, 3, GL_FLOAT, GL_FALSE, 0, nullptr);
    glEnableVertexAttribArray(0);
}


void 
Object::ApplyLights(vector<class Light const*> const& lights) const
{
    // apply lights
    for(auto const& light: lights) {
        switch(light->Type) {
        case Light::LightType::AMBIENT:
            SendUniform("amb_light.color", light->Ambient.Color);
            SendUniform("amb_light.intensity", light->Ambient.Intensity);
            break;
        case Light::LightType::DIFFUSE:
            SendUniform("dif_light.color", light->Diffuse.Color);
            SendUniform("dif_light.intensity", light->Diffuse.Intensity);
            SendUniform("dif_light.direction", light->Diffuse.Direction);
            break;
        default:
            throw "Invalid light type.";
        }
    }
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


void 
Object::SendUniform(string parameter, bool value) const
{
    GLint id = glGetUniformLocation(program.Reference(), parameter.c_str());
    glUniform1i(id, value ? 1 : 0);
}


}

// vim: ts=4:sw=4:sts=4:expandtab
