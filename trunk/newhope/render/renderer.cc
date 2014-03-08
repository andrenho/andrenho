#include "render/renderer.h"

#include "render/box.h"
#include "render/renderengine.h"

extern render::RenderEngine* render_engine;

namespace render {

Renderer::Renderer()
{
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    prog = render_engine->CompileProgram("vertex.glsl", "fragment.glsl");

	GLint posAttrib = glGetAttribLocation(prog, "vert");
	glVertexAttribPointer(posAttrib, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(posAttrib);
}


Renderer::~Renderer()
{
		glDeleteVertexArrays(1, &vao);
}

void 
Renderer::AddObject(class Box* box)
{
    glBufferData(GL_ARRAY_BUFFER, sizeof(box->vertexData), box->vertexData, GL_STATIC_DRAW);

    objects.push_back(box);
}

void
Renderer::Render()
{
    glClearColor(0, 0, 0, 1);
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

    glUseProgram(prog);
    for(auto const& object: objects) {
        glDrawArrays(GL_TRIANGLES, 0, object->NumTriangles());
    }
}

}

// vim: ts=4:sw=4:sts=4:expandtab
