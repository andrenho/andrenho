#ifndef RENDER_CAMERA_H_
#define RENDER_CAMERA_H_

#include <glm/glm.hpp>

namespace render {

class Camera {
public:
    Camera();

    void setPosition(float x, float y, float z);
    void LookAt(float x, float y, float z);

    glm::mat4 Projection() const;
    glm::mat4 View() const;

	Camera(const Camera&) = delete;
    Camera& operator=(const Camera&) = delete;

private:
    glm::vec3 position = { 0, 0, 0 };
    glm::vec3 lookat = { 0, 0, 0 };
};

}

#endif  // RENDER_CAMERA_H_

// vim: ts=4:sw=4:sts=4:expandtab
