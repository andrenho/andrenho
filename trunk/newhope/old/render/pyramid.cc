#include "render/pyramid.h"

#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
namespace render {

Pyramid::Pyramid()
    : Object(), vertices{
        -1, 0,  1,
         1, 0,  1,
         0, 2,  0,

         0, 2,  0,
         0, 0, -1,
        -1, 0, -1,

         0, 0, -1,
         0, 2,  0,
         1, 0,  1,

        -1, 0,  1,
         1, 0,  1,
         0, 0, -1,
    }
{
}


}

// vim: ts=4:sw=4:sts=4:expandtab
