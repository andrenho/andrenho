#include "render/diffuselight.h"

#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <iostream>
using namespace std;

#include "render/program.h"

namespace render {

DiffuseLight::DiffuseLight(RenderEngine const& engine, glm::vec3 color, float intensity, glm::vec3 direction, Program const& program)
    : Light(LightType::DIFFUSE, color), Intensity(intensity), Direction(direction), engine(engine), program(program)
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
    glGenTextures(1, &depth_texture);
    glBindTexture(GL_TEXTURE_2D, depth_texture);
    glTexStorage2D(GL_TEXTURE_2D, 1, GL_RGBA32F, 256, 256);

    // setup texture
    float* data = new float[256 * 256 * 4];
    for(int i=0; i<256*256*4; i++) {
        data[i] = 0x0;
    }
    glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, 256, 256, GL_RGBA, GL_FLOAT, data);
    delete[] data;
}


}

// vim: ts=4:sw=4:sts=4:expandtab
