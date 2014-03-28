#include "render/diffuselight.h"

#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <SOIL/SOIL.h>
#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

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
    SetupDebugTexture();
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
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, depth_texture);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

    // setup texture
    glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT, SHADOW_SIZE, SHADOW_SIZE, 0, GL_DEPTH_COMPONENT, GL_UNSIGNED_BYTE, 0); // TODO

    // attach texture to framebuffer
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, depth_texture, 0);
    GLenum draw_buffers[1] = { GL_NONE };
    glDrawBuffers(1, draw_buffers);
    if(glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE) {
        throw "Could not create framebuffer.";
    }
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}


void
DiffuseLight::SetupDebugTexture()
{
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
}


void 
DiffuseLight::DrawShadows(vector<Object const*> const& objects) const
{
    // bind framebuffer
    glBindFramebuffer(GL_FRAMEBUFFER, fbo);
    glViewport(0, 0, SHADOW_SIZE, SHADOW_SIZE);

    // clear texture
    glClear(GL_DEPTH_BUFFER_BIT);

    // setup projection
    glm::mat4 view = glm::lookAt( 
        glm::vec3(-Direction.x, -Direction.y, -Direction.z), // camera position
        glm::vec3(0, 0, 0), // looking at
        glm::vec3(0,1,0)    // Head is up (set to 0,-1,0 to look upside-down)
    );
    glm::mat4 projection = glm::perspective(
            45.0f,      // FOV
            1.0f,  // aspect
            2.0f,       // near
            10.0f      // far
    );

    // draw objects
    for(auto const& obj: objects) {
        obj->RenderForShadowing(program, projection * view);
    }

    // unbind framebuffer
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    glViewport(0, 0, 800, 600); // TODO
}


void 
DiffuseLight::DebugToScreen() const
{
    // bind framebuffer
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    glUseProgram(debug_program.Reference());
    
    // bind texture
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, depth_texture);

    // draw texture
    debug_program.SendUniform("sampler", 0u);
    glBindVertexArray(debug_vao);
    glDrawArrays(GL_TRIANGLES, 0, 12);
    glBindVertexArray(0);
}


// http://antongerdelan.net/opengl/texture_shadows.html

}

// vim: ts=4:sw=4:sts=4:expandtab
