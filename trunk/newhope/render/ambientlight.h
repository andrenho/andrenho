#ifndef RENDER_AMBIENTLIGHT_H_
#define RENDER_AMBIENTLIGHT_H_

#include "render/light.h"

namespace render {

class AmbientLight : public Light {
public:
    AmbientLight(glm::vec3 color, float intensity) : Light(LightType::AMBIENT, color), Intensity(intensity) {}

    void ApplyLightToObject(Object const& obj, Program const& program) const {
        (void) obj;
        program.SendUniform("amb_light.color", Color);
        program.SendUniform("amb_light.intensity", Intensity);
    }

    const float Intensity;
};

}

#endif  // RENDER_AMBIENTLIGHT_H_

// vim: ts=4:sw=4:sts=4:expandtab
