#include "render/object.h"

#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <algorithm>
#include <cerrno>
#include <fstream>
#include <iostream>
using namespace std;

#include "render/camera.h"

namespace render {

map<string, GLuint> Object::Programs = {};


Object::Object()
{
}


void 
Object::Prepare(class Camera const& camera) const
{
    glUseProgram(program);
    glBindVertexArray(vao);

    // TODO - adjust position and rotation
    glm::mat4 model = glm::mat4(1.0f); // TODO

    GLint mvp_id = glGetUniformLocation(program, "MVP");
    glm::mat4 mvp = camera.Projection() * camera.View() * model;
    glUniformMatrix4fv(mvp_id, 1, GL_FALSE, &mvp[0][0]);
}


GLuint 
Object::SetupProgram(string vertex_shader, string frag_shader)
{
    decltype(Programs)::iterator it = Programs.find(vertex_shader + " " + frag_shader);
    if(it != end(Programs)) {
        return it->second;
    }   

    string v = ReadWholeFile(vertex_shader);
    string f = ReadWholeFile(frag_shader);
	const GLchar* src_v = v.c_str(); 
	const GLchar* src_f = f.c_str();
	GLint isCompiled = GL_FALSE;

	GLuint vshader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vshader, 1, &src_v, NULL);
	glCompileShader(vshader);
	glGetShaderiv(vshader, GL_COMPILE_STATUS, &isCompiled);
	if(isCompiled == GL_FALSE) {
		char buffer[512];
        glGetShaderInfoLog(vshader, 512, NULL, buffer);
        cerr << buffer << endl;
        throw;
	}

	GLuint fshader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fshader, 1, &src_f, NULL);
	glCompileShader(fshader);
	glGetShaderiv(fshader, GL_COMPILE_STATUS, &isCompiled);
	if(isCompiled == GL_FALSE) {
		char buffer[512];
        glGetShaderInfoLog(fshader, 512, NULL, buffer);
        cerr << buffer << endl;
		throw;
	}

	GLuint program = glCreateProgram();
	glAttachShader(program, vshader);
	glAttachShader(program, fshader);
	glLinkProgram(program);

	glDeleteShader(vshader);
	glDeleteShader(fshader);

    Programs[vertex_shader + " " + frag_shader] = program;

	return program;
}


string 
Object::ReadWholeFile(string filename)
{
    ifstream file(filename);
    string content((istreambuf_iterator<char>(file)), istreambuf_iterator<char>());

    return content;
}


}

// vim: ts=4:sw=4:sts=4:expandtab
