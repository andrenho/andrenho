#include "render/diffuselight.h"

#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "render/program.h"

namespace render {

DiffuseLight::DiffuseLight(glm::vec3 color, float intensity, glm::vec3 direction, Program const& program)
    : Light(LightType::DIFFUSE, color), Intensity(intensity), Direction(direction), program(program)
{
    InitShadowMap();
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
DiffuseLight::InitShadowMap()
{
    /*
    int WindowWidth = 800, WindowHeight = 600; // TODO

    // Create the FBO
    glGenFramebuffers(1, &fbo);
    glBindFramebuffer(GL_FRAMEBUFFER, fbo);

    // Create the depth buffer
    glGenTextures(1, &depth_texture);
    glBindTexture(GL_TEXTURE_2D, depth_texture);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT16, WindowWidth, WindowHeight, 0, GL_DEPTH_COMPONENT, GL_FLOAT, nullptr);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);

    glFramebufferTexture(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, depth_texture, 0);
    glDrawBuffer(GL_NONE);

    if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE) {
        throw "FB error";
    }*/
}


void
DiffuseLight::PrepareShadowMap()
{
}


void 
DiffuseLight::BindForWriting() const
{
    glBindFramebuffer(GL_DRAW_FRAMEBUFFER, fbo);
}


void 
DiffuseLight::BindForReading(GLenum texture_unit) const
{
    glActiveTexture(texture_unit);
    glBindTexture(GL_TEXTURE_2D, depth_texture);
}



}

// vim: ts=4:sw=4:sts=4:expandtab
