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

class Object {
    friend class OBJ_Loader;

public:
    Object(string const& origin, class Program const& program);
    virtual ~Object() {}

    inline void Rotate(float x, float y) { rotation_x += x; rotation_y += y; }
    inline void Translate(float x, float y, float z) { translate_x += x; translate_y += y; translate_z += z; }

    void Render(class Camera const& camera) const;

private:
    void SetupObject();
    void UploadVertices(vector<glm::vec3> const& vertices, GLuint& vbo);
    void UploadElements(vector<array<int,3>> const& elements, GLuint& ebo);
    void LinkVertexArray(string const& variable, GLuint vbo, GLuint ebo);

    void SendUniform(string parameter, glm::mat4 value) const;
    void SendUniform(string parameter, glm::vec3 value) const;
    void SendUniform(string parameter, float value) const;

    class Program const& program;

    vector<glm::vec3> vertices = {};
    vector<array<int,3>> triangles = {};
    vector<glm::vec3> normal_vertices = {};
    vector<array<int,3>> normals = {};

    float rotation_x = 0, rotation_y = 0;
    float translate_x = 0, translate_y = 0, translate_z = 0;
    float scale = 1;

    GLuint vao = 0,
           vbo = 0,
           vbo_normals = 0,
           ebo = 0,
           ebo_normals = 0;

    // ---

	Object(const Object&) = delete;
    Object& operator=(const Object&) = delete;
};

}

#endif  // RENDER_OBJECT_H_

// vim: ts=4:sw=4:sts=4:expandtab
