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
using namespace std;

namespace render {

class Object {
public:
    inline void Rotate(float x, float y) { rotation_x += x; rotation_y += y; }
    inline void Translate(float x, float y, float z) { translate_x += x; translate_y += y; translate_z += z; }

    void Prepare(class Camera const& camera) const;
    virtual void Render() const = 0;

protected:
    Object();
    virtual ~Object() {}

    GLuint SetupProgram(string vertex_shader, string frag_shader);
    void SendUniformMatrix(string parameter, glm::mat4 value) const;

    GLuint vao = 0, 
           vbo = 0, 
           program = 0;

	Object(const Object&) = delete;
    Object& operator=(const Object&) = delete;

private:
    string ReadWholeFile(string filename);
    float rotation_x = 0, rotation_y = 0;
    float translate_x = 0, translate_y = 0, translate_z = 0;
    float scale = 1;

    static map<string, GLuint> Programs;
};

}

#endif  // RENDER_OBJECT_H_

// vim: ts=4:sw=4:sts=4:expandtab
