#ifndef RENDER_DIFFUSELIGHT_H_
#define RENDER_DIFFUSELIGHT_H_

#include "render/light.h"

namespace render {

class DiffuseLight : public Light {
public:
    DiffuseLight(glm::vec3 color, float intensity, glm::vec3 direction, class Program const& program);

    void ApplyLightToObject(Object const& obj, Program const& prog) const;
    void BindForWriting() const;
    void BindForReading(GLenum texture_unit) const;

    const float Intensity;
    const glm::vec3 Direction;

private:
    void InitShadowMap();

    GLuint fbo = 0,
           depth_texture = 0;
    class Program const& program;
};

}

#endif  // RENDER_DIFFUSELIGHT_H_

// vim: ts=4:sw=4:sts=4:expandtab
