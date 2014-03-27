#include "render/diffuselight.h"

#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <SOIL/SOIL.h>

#include <iostream>
using namespace std;

#include "render/ambientlight.h"
#include "render/camera.h"
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
    // create framebuffer
    glGenFramebuffers(1, &fbo);
    glBindFramebuffer(GL_FRAMEBUFFER, fbo);

    // create texture
    glGenTextures(1, &depth_texture);
    glBindTexture(GL_TEXTURE_2D, depth_texture);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

    // create depth buffer
    GLuint depth_renderbuffer;
    glGenRenderbuffers(1, &depth_renderbuffer);
    glBindRenderbuffer(GL_RENDERBUFFER, depth_renderbuffer);
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, 800, 600);
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, depth_renderbuffer);

    // setup texture
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, 800, 600, 0, GL_RGBA, GL_UNSIGNED_BYTE, 0); // TODO

    // bind texture to framebuffer
    glFramebufferTexture(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, depth_texture, 0);
    GLenum draw_buffers[1] = { GL_COLOR_ATTACHMENT0 };
    glDrawBuffers(1, draw_buffers);
    if(glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE) {
        throw "Could not create framebuffer.";
    }

    // setup debug
    glGenVertexArrays(1, &debug_vao);
    glBindVertexArray(debug_vao);

    GLfloat vertex[] = {
        -1.0f,-1.0f,   0.0f, 0.0f,
        -0.7f,-1.0f,   1.0f, 0.0f,
        -1.0f,-0.7f,   0.0f, 1.0f,
        -0.7f,-1.0f,   1.0f, 0.0f,
        -0.7f,-0.7f,   1.0f, 1.0f,
        -1.0f,-0.7f,   0.0f, 1.0f,
    };
    glGenBuffers(1, &debug_vbo);
    glBindBuffer(GL_ARRAY_BUFFER, debug_vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertex), vertex, GL_STATIC_DRAW);
    debug_program.SendVertexArray("vert", 2, 4, 0);
    debug_program.SendVertexArray("v_uv", 2, 4, 2, true);
    
    // unbind VAO & VBO
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    // unbind framebuffer
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}


void 
DiffuseLight::DrawShadows(vector<Object const*> const& objects) const
{
    glBindFramebuffer(GL_FRAMEBUFFER, fbo);
    glViewport(0, 0, 800, 600); // TODO

    glClearColor(0, 0, 0, 1);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    Camera camera(engine);
    camera.LookAt(0, 0, 0);
    camera.setPosition(-Direction.x, -Direction.y, -Direction.z);
    vector<Light const*> lights = { 
        new AmbientLight(glm::vec3(1.0f, 1.0f, 1.0f), 0.8f),
    };
    for(auto const& obj: objects) {
        obj->Prepare(camera, lights, &program);
        obj->Render();
    }
    delete lights[0];

    glClearColor(0, 0, 0, 1);
}


void 
DiffuseLight::DebugToScreen() const
{
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    glUseProgram(debug_program.Reference());
    
    debug_program.SendUniform("sampler", 0u);
    
    glBindVertexArray(debug_vao);
    glDrawArrays(GL_TRIANGLES, 0, 12);
    glBindVertexArray(0);
}

}

// vim: ts=4:sw=4:sts=4:expandtab
