#ifndef RENDER_OBJECT_H_
#define RENDER_OBJECT_H_

#define GLEW_STATIC
#include <GL/glew.h>

namespace render {

class Object {
public:
    Object();

	Object(const Object&) = delete;
    Object& operator=(const Object&) = delete;

    virtual const float* Vertices() const = 0;
    virtual int VerticesSize() const = 0;
    virtual int NumVertices() const = 0;

    virtual void UploadToGPU(unsigned int program) = 0;

protected:
    GLuint vbo = 0;
};

}

#endif  // RENDER_OBJECT_H_

// vim: ts=4:sw=4:sts=4:expandtab
