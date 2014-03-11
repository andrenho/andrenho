#include "render/square.h"

#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
namespace render {

Square::Square()
    : Object(), vertices{
        -0.5f, -0.5f, 0.0f,
         0.5f, -0.5f, 0.0f,
         0.5f,  0.5f, 0.0f,
    }, mvp_id(0)
{
}


}

// vim: ts=4:sw=4:sts=4:expandtab
