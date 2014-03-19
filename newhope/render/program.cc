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


string 
Program::ReadWholeFile(string filename)
{
    ifstream file(filename);
    string content((istreambuf_iterator<char>(file)), istreambuf_iterator<char>());

    return content;
}

}

// vim: ts=4:sw=4:sts=4:expandtab
