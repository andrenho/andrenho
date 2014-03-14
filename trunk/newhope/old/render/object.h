#ifndef RENDER_OBJECT_H_
#define RENDER_OBJECT_H_

#define GLEW_STATIC
#include <GL/glew.h>

#include <glm/glm.hpp>

namespace render {

class Object {
public:
    Object();

	Object(const Object&) = delete;
    Object& operator=(const Object&) = delete;

    virtual void Prepare(glm::mat4 projection, glm::mat4 view);

    virtual const float* Vertices() const = 0;
    virtual int NumVertices() const = 0;

    virtual void UploadToGPU();
    virtual glm::vec3 Position() const = 0;

    virtual void Setup(unsigned int program);
    virtual glm::mat4 ModelMatrix() const;


protected:
    GLuint mvp_id = 0;
    GLuint vbo = 0;
};

}

#endif  // RENDER_OBJECT_H_

// vim: ts=4:sw=4:sts=4:expandtab
