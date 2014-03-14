#ifndef RENDER_OBJECT_H_
#define RENDER_OBJECT_H_

#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <map>
#include <string>
using namespace std;

namespace render {

class Object {
public:
    void Prepare(class Camera const& camera) const;
    virtual void Render() const = 0;

protected:
    Object();
    virtual ~Object() {}

    GLuint SetupProgram(string vertex_shader, string frag_shader);

    GLuint vao = 0, 
           vbo = 0, 
           program = 0;

	Object(const Object&) = delete;
    Object& operator=(const Object&) = delete;

private:
    string ReadWholeFile(string filename);

    static map<string, GLuint> Programs;
};

}

#endif  // RENDER_OBJECT_H_

// vim: ts=4:sw=4:sts=4:expandtab
