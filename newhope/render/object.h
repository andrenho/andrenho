#ifndef RENDER_OBJECT_H_
#define RENDER_OBJECT_H_

#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <map>
#include <string>
#include <vector>
using namespace std;

namespace render {

struct Vertice {
    glm::vec3 Point;
    glm::vec3 Normal;
    glm::vec3 Color;
};

class Object {
public:
    Object(string const& origin, class Program const& program);
    virtual ~Object() {}

    inline void Rotate(float x, float y) { rotation_x += x; rotation_y += y; }
    inline void Translate(float x, float y, float z) { translate_x += x; translate_y += y; translate_z += z; }
    inline void setSmooth(bool v) { smooth = v; }

    void PrepareForShadowing(class Program const& sh_program, glm::mat4 view) const;
    void Prepare(class Camera const& camera, vector<class Light const*> const& lights) const;
    void Render() const;

private:
    void SetupObject();

    class Program const& program;

    vector<Vertice> vertices = {};

    float rotation_x = 0, rotation_y = 0;
    float translate_x = 0, translate_y = 0, translate_z = 0;
    float scale = 1;

    bool smooth = false;

    GLuint vao = 0,
           vbo = 0,
           ebo = 0,
           vbo_normals = 0,
           ebo_normals = 0;

    // ---

	Object(const Object&) = delete;
    Object& operator=(const Object&) = delete;
};

}

#endif  // RENDER_OBJECT_H_

// vim: ts=4:sw=4:sts=4:expandtab
