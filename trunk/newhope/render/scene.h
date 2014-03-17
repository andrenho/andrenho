#ifndef RENDER_SCENE_H_
#define RENDER_SCENE_H_

#include <vector>
using namespace std;

namespace render {

class Scene {
public:
    Scene(class Camera const& camera);

    enum Mode { FILL, WIREFRAME };

    void AddObject(class Object const& obj);
    void setMode(enum Mode mode);
    enum Mode Mode() const { return mode; }

    void Render() const;

	Scene(const Scene&) = delete;
    Scene& operator=(const Scene&) = delete;

private:
    class Camera const& camera;
    vector<const Object*> objects = {};
    enum Mode mode = FILL;
};

}

#endif  // RENDER_SCENE_H_

// vim: ts=4:sw=4:sts=4:expandtab
