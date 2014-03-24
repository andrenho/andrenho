#ifndef RENDER_PROGRAM_H_
#define RENDER_PROGRAM_H_

#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

#include <string>
using namespace std;

namespace render {

class Program {
public:
    Program(string vertex_shader, string fragment_shader);
    ~Program();

    GLuint Reference() const { return reference; }

    void SendUniform(string parameter, glm::mat4 value) const;
    void SendUniform(string parameter, glm::vec3 value) const;
    void SendUniform(string parameter, float value) const;
    void SendUniform(string parameter, bool value) const;
    void SendUniform(string parameter, unsigned int value) const;

    void SendVertexArray(string paramter, int float_count, int stride) const;

	Program(const Program&) = delete;
    Program& operator=(const Program&) = delete;

private:
    string ReadWholeFile(string filename);

    GLuint reference = 0;
};

}

#endif  // RENDER_PROGRAM_H_

// vim: ts=4:sw=4:sts=4:expandtab
