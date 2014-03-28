#include "render/object.h"

#include <iostream>
using namespace std;

#include "render/ambientlight.h"
#include "render/camera.h"
#include "render/diffuselight.h"
#include "render/obj_loader.h"
#include "render/program.h"

namespace render {

Object::Object(string const& origin, Program const& program)
    : program(program)
{
    if(origin.compare(origin.length()-4, 4, ".obj") == 0) {
        OBJ_Loader loader;
        loader.Load(origin, vertices);
    } else {
        throw "Invalid file extension for file " + origin;
    }
    SetupObject();
}


glm::mat4 
Object::Model() const
{
    // translate, rotate and scale
    glm::mat4 translate = glm::translate(
            glm::mat4(1.0f), 
            glm::vec3(translate_x, translate_y, translate_z));
    glm::mat4 rotate_x = glm::rotate(translate, rotation_x, glm::vec3(1.0f, 0.0f, 0.0f));
    glm::mat4 rotate_y = glm::rotate(rotate_x, rotation_y, glm::vec3(0.0f, 1.0f, 0.0f));
    // TODO - glm::mat4 scale = glm::scale(rotate_y, glm::vec3(scale, scale, scale));

    return rotate_y;
}


void 
Object::Render(class Camera const& camera, vector<class Light const*> const& lights) const
{
    // setup program
    glUseProgram(program.Reference());

    // send camera + model information
    program.SendUniform("wvp", camera.Projection() * camera.View() * Model());

    // flat/smooth
    program.SendUniform("smooth_model", smooth);

    // apply lights
    for(auto const& light: lights) {
        light->ApplyLightToObject(*this, program);
    }

    // render
    RenderObject();

    glUseProgram(0);
}


void 
Object::RenderForShadowing(class Program const& shprog, glm::mat4 vp) const
{
    // setup program
    glUseProgram(shprog.Reference());

    // send camera + model information
    program.SendUniform("wvp", vp * Model());

    // render
    RenderObject();

    glUseProgram(0);
}


void
Object::RenderObject() const
{
    glBindVertexArray(vao);
    glDrawArrays(GL_TRIANGLES, 0, static_cast<GLsizei>(vertices.size()));
    glBindVertexArray(0);
}


void
Object::SetupObject()
{
    // initialize VAO
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    // send vertices to GPU
    vector<GLfloat> vertex;
    for(auto const& vertice: vertices) {
        for(int j=0; j<3; j++) { vertex.push_back(vertice.Point[j]); }
        for(int j=0; j<3; j++) { vertex.push_back(vertice.Normal[j]); }
        for(int j=0; j<3; j++) { vertex.push_back(vertice.Color[j]); }
    }
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, vertex.size() * sizeof(GLfloat), &vertex[0], GL_STATIC_DRAW);

    // bind variables
    glBindBuffer(GL_ARRAY_BUFFER, vbo); // TODO
    program.SendVertexArray("vert", 3, 9, 0);
    program.SendVertexArray("normals", 3, 9, 3);
    program.SendVertexArray("material_color", 3, 9, 6);
    
    // unbind VAO & VBO
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    // TODO - clear mesh
}


}

// vim: ts=4:sw=4:sts=4:expandtab
