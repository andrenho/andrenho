#ifndef RENDER_DIFFUSELIGHT_H_
#define RENDER_DIFFUSELIGHT_H_

#include "render/light.h"

namespace render {

class DiffuseLight : public Light {
public:
    DiffuseLight(class RenderEngine const& engine, glm::vec3 color, float intensity, glm::vec3 direction, class Program const& program);

    void ApplyLightToObject(Object const& obj, Program const& prog) const;

    const float Intensity;
    const glm::vec3 Direction;

private:
    void CreateDepthTexture();

    class RenderEngine const& engine;
    class Program const& program;
    GLuint depth_texture = 0;
};

}

#endif  // RENDER_DIFFUSELIGHT_H_

// vim: ts=4:sw=4:sts=4:expandtab
