#include "render/renderer.h"

#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "render/object.h"
#include "render/renderengine.h"

extern render::RenderEngine* render_engine;

namespace render {

Renderer::Renderer()
{
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao); // TODO

}


Renderer::~Renderer()
{
    glDeleteVertexArrays(1, &vao);
}

void 
Renderer::AddObject(Object* obj)
{
    obj->UploadToGPU();
    objects.push_back(obj);
}

void
Renderer::Setup()
{
    prog = render_engine->CompileProgram("vertex.glsl", "fragment.glsl");
    for(auto const& object: objects) {
        object->Setup(prog);
    }
}

void
Renderer::Render()
{
    glm::mat4 projection = glm::perspective(45.0f, 4.0f / 3.0f, 0.1f, 100.0f);
    glm::mat4 view = glm::lookAt( 
            cam_position,
            cam_lookat,
            glm::vec3(0,1,0)  // Head is up (set to 0,-1,0 to look upside-down)
    );

    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

    glUseProgram(prog);
    for(auto const& object: objects) {
        object->Prepare(projection, view);
        glDrawArrays(GL_TRIANGLES, 0, object->NumVertices());
    }
}

}

// vim: ts=4:sw=4:sts=4:expandtab
