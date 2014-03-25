#include "render/diffuselight.h"

#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <SOIL/SOIL.h>

#include <iostream>
using namespace std;

#include "render/program.h"

namespace render {

DiffuseLight::DiffuseLight(RenderEngine const& engine, glm::vec3 color, float intensity, glm::vec3 direction, Program const& program)
    : Light(LightType::DIFFUSE, color), Intensity(intensity), Direction(direction), engine(engine), program(program),
      debug_program("shaders/debug_light.vs", "shaders/debug_light.fs")
{
    CreateDepthTexture();
}


void 
DiffuseLight::ApplyLightToObject(Object const& obj, Program const& program) const
{
    (void) obj;
    program.SendUniform("dif_light.color", Color);
    program.SendUniform("dif_light.intensity", Intensity);
    program.SendUniform("dif_light.direction", Direction);
}


void 
DiffuseLight::CreateDepthTexture()
{
    // create texture
    glEnable(GL_TEXTURE_2D);
    glActiveTexture(GL_TEXTURE0);
    glGenTextures(1, &depth_texture);
    glBindTexture(GL_TEXTURE_2D, depth_texture);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);

    // setup texture
    int w, h;
    unsigned char* image = SOIL_load_image("256x256.png", &w, &h, 0, SOIL_LOAD_RGBA);
    if(!image) {
        throw "File not found.";
    }
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, w, h, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
    SOIL_free_image_data(image);

    // setup debug
    glGenVertexArrays(1, &debug_vao);
    glBindVertexArray(debug_vao);

    GLfloat vertex[] = {
        /* 0.0f, 0.8f,    0.5f, 1.0f,
        -0.8f,-0.8f,    0.0f, 0.0f,
         0.8f,-0.8f,    1.0f, 0.0f,*/
        -1.0f,-1.0f,   0.0f, 0.0f,
         1.0f,-1.0f,   1.0f, 0.0f,
        -1.0f, 1.0f,   0.0f, 1.0f,
         1.0f,-1.0f,   1.0f, 0.0f,
         1.0f, 1.0f,   1.0f, 1.0f,
        -1.0f, 1.0f,   0.0f, 1.0f,
    };
    glGenBuffers(1, &debug_vbo);
    glBindBuffer(GL_ARRAY_BUFFER, debug_vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertex), vertex, GL_STATIC_DRAW);
    debug_program.SendVertexArray("vert", 2, 4, 0);
    debug_program.SendVertexArray("v_uv", 2, 4, 2, true);
    
    // unbind VAO & VBO
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}


void 
DiffuseLight::DebugToScreen() const
{
    glUseProgram(debug_program.Reference());
    
    debug_program.SendUniform("sampler", 0u);
    
    glBindVertexArray(debug_vao);
    glDrawArrays(GL_TRIANGLES, 0, 12);
    glBindVertexArray(0);
}

}

// vim: ts=4:sw=4:sts=4:expandtab
