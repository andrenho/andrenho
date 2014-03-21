#ifndef RENDER_LIGHT_H_
#define RENDER_LIGHT_H_

#include <glm/glm.hpp>
#include <cassert>

namespace render {

struct Light {
    enum LightType { AMBIENT, DIFFUSE } Type;
    
    union {
        struct {
            glm::vec3 Color;
            float Intensity;
        } Ambient;

        struct {
            glm::vec3 Color;
            float Intensity;
            glm::vec3 Direction;
        } Diffuse;
    };

    Light(enum LightType Type, float r, float g, float b, float Intensity)
        : Type(Type), Ambient({ glm::vec3 { r, g, b }, Intensity }) { assert(Type == LightType::AMBIENT); }
    Light(enum LightType Type, float r, float g, float b, float Intensity, float x, float y, float z)
        : Type(Type), Diffuse({ glm::vec3 { r, g, b }, Intensity, glm::vec3 { x, y, z } }) { assert(Type == LightType::DIFFUSE); }
};

}

#endif  // RENDER_LIGHT_H_

// vim: ts=4:sw=4:sts=4:expandtab
