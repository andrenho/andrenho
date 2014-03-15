#include "render/object.h"

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

    // send camera info
    SendUniformMatrix("projection", camera.Projection());
    SendUniformMatrix("camera", camera.View());

    // translate, rotate and scale
    glm::mat4 translate = glm::translate(
            glm::mat4(1.0f), 
            glm::vec3(translate_x, translate_y, translate_z));
    glm::mat4 rotate_x = glm::rotate(translate, rotation_x, glm::vec3(1.0f, 0.0f, 0.0f));
    glm::mat4 rotate_y = glm::rotate(rotate_x, rotation_y, glm::vec3(0.0f, 1.0f, 0.0f));
    // TODO - glm::mat4 scale = glm::scale(rotate_y, glm::vec3(scale, scale, scale));
    SendUniformMatrix("model", rotate_y);
}


void 
Object::SendUniformMatrix(string parameter, glm::mat4 value) const
{
    GLint id = glGetUniformLocation(program, parameter.c_str());
    glUniformMatrix4fv(id, 1, GL_FALSE, &value[0][0]);
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
