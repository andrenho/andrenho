#ifndef RENDER_CAMERA_H_
#define RENDER_CAMERA_H_

class Camera {
public:
    Camera();

	Camera(const Camera&) = delete;
    Camera& operator=(const Camera&) = delete;
};

#endif  // RENDER_CAMERA_H_

// vim: ts=4:sw=4:sts=4:expandtab
