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
    glGenTextures(1, &depth_texture);
    glBindTexture(GL_TEXTURE_2D, depth_texture);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);

    // setup texture
    /*
    GLubyte* data = new GLubyte[256 * 256 * 4];
    GLubyte j=0xff;
    for(int i=0; i<256*256*4; i+=4) {
        data[i] = data[i+2] = 0x80;
        data[i+1] = j;
        data[i+3] = 0xff;
        j = 0x0;
    }*/
    int w, h;
    unsigned char* image = SOIL_load_image("256x256.jpg", &w, &h, 0, SOIL_LOAD_RGB);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, 256, 256, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
    //delete[] data;

    // setup debug
    glGenVertexArrays(1, &debug_vao);
    glBindVertexArray(debug_vao);

    GLfloat vertex[] = {
         0.000000, 0.000000, 0, 0,
         1.000000, 0.000000, 1, 0,
         0.000000, 1.000000, 0, 1,
         1.000000, 0.000000, 1, 0,
         1.000000, 1.000000, 1, 1,
         0.000000, 1.000000, 0, 1,
    };
    glGenBuffers(1, &debug_vbo);
    glBindBuffer(GL_ARRAY_BUFFER, debug_vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertex), vertex, GL_STATIC_DRAW);

    // bind debug variables
    glBindBuffer(GL_ARRAY_BUFFER, debug_vbo);
    program.SendVertexArray("vert", 4, 0);
    program.SendVertexArray("v_uv", 4, 2);
    
    // unbind VAO & VBO
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}


void 
DiffuseLight::DebugToScreen() const
{
    glUseProgram(debug_program.Reference());
    
    debug_program.SendUniform("sampler", depth_texture);
    
    glBindVertexArray(debug_vao);
    glDrawArrays(GL_TRIANGLES, 0, 12);
    glBindVertexArray(0);
}

}

// vim: ts=4:sw=4:sts=4:expandtab
