#include "render/object.h"

namespace render {

Object::Object()
{
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
}

}

// vim: ts=4:sw=4:sts=4:expandtab
