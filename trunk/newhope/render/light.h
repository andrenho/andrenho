#ifndef RENDER_LIGHT_H_
#define RENDER_LIGHT_H_

#include <glm/glm.hpp>
#include <cassert>

#include "render/object.h"
#include "render/program.h"

namespace render {

class Light {
public:
    virtual ~Light() {}

    virtual void ApplyLightToObject(Object const& obj, Program const& prog) const = 0;
    virtual void RenderShadow(vector<Object const*> const& objects) const { (void)objects; }

    const enum LightType { AMBIENT, DIFFUSE } Type;
    const glm::vec3 Color;

protected:
    Light(enum LightType type, glm::vec3 color) : Type(type), Color(color) {}
};

}

#endif  // RENDER_LIGHT_H_

// vim: ts=4:sw=4:sts=4:expandtab
