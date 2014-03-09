#include "render/renderengine.h"
#include "render/renderer.h"
#include "render/triangle.h"

render::RenderEngine* render_engine = nullptr;

int main()
{
    render_engine = new render::RenderEngine("newhope 0.0.1");
    render::Renderer renderer;

    render_engine->setRenderer(&renderer);

    renderer.AddObject(new render::Triangle());
    renderer.Setup();

    while(render_engine->Active()) {
        render_engine->ProcessEvents();
        render_engine->Render();
    }
}

// vim: ts=4:sw=4:sts=4:expandtab
