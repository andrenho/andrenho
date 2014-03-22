#include "render/shadowmap.h"

ShadowMap::ShadowMap()
{
}


void
ShadowMap::Init()
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
    }
    */
}

// vim: ts=4:sw=4:sts=4:expandtab
