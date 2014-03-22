#include "render/program.h"

#include <algorithm>
#include <cerrno>
#include <fstream>
#include <iostream>
using namespace std;


namespace render {

Program::Program(string vertex_shader, string frag_shader)
{
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

	reference = glCreateProgram();
	glAttachShader(reference, vshader);
	glAttachShader(reference, fshader);
	glLinkProgram(reference);

	glDeleteShader(vshader);
	glDeleteShader(fshader);
}


Program::~Program()
{
    glDeleteProgram(reference);
}


void 
Program::SendUniform(string parameter, glm::mat4 value) const
{
    GLint id = glGetUniformLocation(Reference(), parameter.c_str());
    glUniformMatrix4fv(id, 1, GL_FALSE, &value[0][0]);
}


void 
Program::SendUniform(string parameter, glm::vec3 value) const
{
    GLint id = glGetUniformLocation(Reference(), parameter.c_str());
    glUniform3fv(id, 1, &value[0]);
}


void 
Program::SendUniform(string parameter, float value) const
{
    GLint id = glGetUniformLocation(Reference(), parameter.c_str());
    glUniform1f(id, value);
}


void 
Program::SendUniform(string parameter, bool value) const
{
    GLint id = glGetUniformLocation(Reference(), parameter.c_str());
    glUniform1i(id, value ? 1 : 0);
}


void 
Program::SendVertexArray(string parameter, int float_count, int stride) const
{
    GLint variable_id = glGetAttribLocation(Reference(), parameter.c_str());
    glEnableVertexAttribArray(variable_id);
    glVertexAttribPointer(variable_id, 3, GL_FLOAT, GL_FALSE, 
            static_cast<GLsizei>(float_count*sizeof(GLfloat)), 
            reinterpret_cast<void*>(stride*sizeof(GLfloat)));
}


string 
Program::ReadWholeFile(string filename)
{
    ifstream file(filename);
    string content((istreambuf_iterator<char>(file)), istreambuf_iterator<char>());

    return content;
}

}

// vim: ts=4:sw=4:sts=4:expandtab
