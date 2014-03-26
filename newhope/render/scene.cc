#include "render/scene.h"

#include <cstdlib>

#include "render/camera.h"
#include "render/diffuselight.h"
#include "render/object.h"

namespace render {

Scene::Scene(Camera const& camera)
    : camera(camera)
{
}


void 
Scene::AddObject(Object const& obj)
{
    objects.push_back(&obj);
}


void
Scene::AddLight(Light const& light)
{
    lights.push_back(&light);
}


void 
Scene::setMode(enum Mode mode)
{
    this->mode = mode;
    if(mode == WIREFRAME) {
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    } else if(mode == FILL) {
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    } else {
        abort();
    }
}


void
Scene::Render() const
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // draw shadows
    /*
    for(auto const& light: lights) {
        light->RenderShadow(objects);
    }*/

    // draw scene
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    for(auto const& obj: objects) {
        obj->Prepare(camera, lights);
        obj->Render();
    }

    // draw debugging shadow image
    dynamic_cast<DiffuseLight const*>(lights[1])->DebugToScreen();

    glBindVertexArray(0);
    glUseProgram(0);
}


}

// vim: ts=4:sw=4:sts=4:expandtab
