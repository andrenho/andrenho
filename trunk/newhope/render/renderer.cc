#include "render/renderer.h"

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
    glBufferData(GL_ARRAY_BUFFER, obj->VerticesSize() * sizeof(float), obj->Vertices(), GL_STATIC_DRAW);
    objects.push_back(obj);
}

void
Renderer::Setup()
{
    prog = render_engine->CompileProgram("vertex.glsl", "fragment.glsl");
    for(auto const& object: objects) {
        object->UploadToGPU(prog);
    }
}

void
Renderer::Render()
{
    glClearColor(0, 0, 0, 1);
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

    glUseProgram(prog);
    for(auto const& object: objects) {
        glDrawArrays(GL_TRIANGLES, 0, object->NumVertices());
    }
}

}

// vim: ts=4:sw=4:sts=4:expandtab
