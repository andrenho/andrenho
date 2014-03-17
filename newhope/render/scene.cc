#include "render/scene.h"

#include <cstdlib>

#include "render/camera.h"
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
    for(auto const& obj: objects) {
        obj->Prepare(camera);
        obj->Render();
    }
}


}

// vim: ts=4:sw=4:sts=4:expandtab
