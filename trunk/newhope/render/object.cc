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
        OBJ_Loader loader;
        loader.Load(origin, *this);
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
    SendUniform("smooth_model", smooth);

    // apply lights
    ApplyLights(lights);

    // draw elements
    glBindVertexArray(vao);
    glDrawArrays(GL_TRIANGLES, 0, triangles.size()*3);
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

    // send vertices to GPU
    assert(triangles.size() == normals.size());
    size_t sz = triangles.size();
    vector<GLfloat> vertex;
    for(int i=0; i<sz; i++) {
        for(int j=0; j<3; j++) {
            vertex.push_back(vertices[triangles[i][j]-1].x);
            vertex.push_back(vertices[triangles[i][j]-1].y);
            vertex.push_back(vertices[triangles[i][j]-1].z);
            vertex.push_back(normal_vertices[normals[i][j]-1].x);
            vertex.push_back(normal_vertices[normals[i][j]-1].y);
            vertex.push_back(normal_vertices[normals[i][j]-1].z);
            vertex.push_back(vertices_colors[triangles[i][j]-1].r);
            vertex.push_back(vertices_colors[triangles[i][j]-1].g);
            vertex.push_back(vertices_colors[triangles[i][j]-1].b);
        }
    }
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, vertex.size() * sizeof(GLfloat), &vertex[0], GL_STATIC_DRAW);
    
    // bind variables
    glBindBuffer(GL_ARRAY_BUFFER, vbo); // TODO
    GLint variable_id = glGetAttribLocation(program.Reference(), "vert");
    glEnableVertexAttribArray(variable_id);
    glVertexAttribPointer(variable_id, 3, GL_FLOAT, GL_FALSE, 9*sizeof(GLfloat), nullptr);

    variable_id = glGetAttribLocation(program.Reference(), "normals");
    glEnableVertexAttribArray(variable_id);
    glVertexAttribPointer(variable_id, 3, GL_FLOAT, GL_FALSE, 9*sizeof(GLfloat), (void*)(3*sizeof(GLfloat)));

    variable_id = glGetAttribLocation(program.Reference(), "material_color");
    glEnableVertexAttribArray(variable_id);
    glVertexAttribPointer(variable_id, 3, GL_FLOAT, GL_FALSE, 9*sizeof(GLfloat), (void*)(6*sizeof(GLfloat)));

    // unbind VAO & VBO
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    // TODO - clear mesh
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
