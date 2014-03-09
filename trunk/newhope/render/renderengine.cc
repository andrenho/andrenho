#include "render/renderengine.h"

#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <cerrno>
#include <fstream>
#include <iostream>
using namespace std;

namespace render {

RenderEngine::RenderEngine(string window_name)
{
	// initalize GLFW
	glfwInit();

	// create hints for OpenGL
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
	
	// create window
	window = glfwCreateWindow(800, 600, window_name.c_str(), nullptr, nullptr);

	// make OpenGL context active
	glfwMakeContextCurrent(window);

	// GLEW
	glewExperimental = GL_TRUE;
	glewInit();
}


RenderEngine::~RenderEngine()
{
	// terminate GLFW
	glfwTerminate();
}


bool 
RenderEngine::Active() const
{
    return !glfwWindowShouldClose(window);
}


void
RenderEngine::ProcessEvents() 
{
    glfwPollEvents();
}


void 
RenderEngine::Render()
{
    if(renderer) {
        renderer->Render();
    }
    glfwSwapBuffers(window);
}


GLuint 
RenderEngine::CompileProgram(string vs_src, string fs_src)
{
    string v = ReadWholeFile(vs_src);
    string f = ReadWholeFile(fs_src);
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

	return program;
}


string 
RenderEngine::ReadWholeFile(string filename)
{
    ifstream file(filename);
    string content((istreambuf_iterator<char>(file)), istreambuf_iterator<char>());

    return content;
}

}

// vim: ts=4:sw=4:sts=4:expandtab
