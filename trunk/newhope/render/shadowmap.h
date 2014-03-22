#ifndef RENDER_SHADOWMAP_H_
#define RENDER_SHADOWMAP_H_

#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>

class ShadowMap {
public:
    ShadowMap();

    void Init();

private:
    GLuint fbo = 0,
           depth_texture = 0;

	ShadowMap(const ShadowMap&) = delete;
    ShadowMap& operator=(const ShadowMap&) = delete;
};

#endif  // RENDER_SHADOWMAP_H_

// vim: ts=4:sw=4:sts=4:expandtab
