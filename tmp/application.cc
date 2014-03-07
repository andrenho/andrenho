// linux: g++ -Wall -g -c application.cc -std=c++11 -lglfw3dll -lopengl32 -lglew32.dll -o application.o

#include "application.h"

#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <cerrno>
#include <ctime>
#include <fstream>
#include <iostream>

Application::Application()
{
	// initalize GLFW
	glfwInit();

	// create hints for OpenGL
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
	
	// create window
	window = glfwCreateWindow(800, 600, "OpenGL", nullptr, nullptr);

	// make OpenGL context active
	glfwMakeContextCurrent(window);

	// GLEW
	glewExperimental = GL_TRUE;
	glewInit();
}


Application::~Application()
{
	// terminate GLFW
	glfwTerminate();
}


void 
Application::Run()
{
	while(!glfwWindowShouldClose(window)) {
		Render((float)clock() / (float)CLOCKS_PER_SEC);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}
}


GLuint 
Application::CompileProgram(string vs_src, string fs_src)
{
	const GLchar* src_v = ReadWholeFile(vs_src).c_str();
	const GLchar* src_f = ReadWholeFile(fs_src).c_str();
	GLint isCompiled = GL_FALSE;

	GLuint vshader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vshader, 1, &src_v, NULL);
	glCompileShader(vshader);
	glGetShaderiv(vshader, GL_COMPILE_STATUS, &isCompiled);
	if(isCompiled == GL_FALSE) {
		throw;
	}

	GLuint fshader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fshader, 1, &src_f, NULL);
	glCompileShader(fshader);
	glGetShaderiv(fshader, GL_COMPILE_STATUS, &isCompiled);
	if(isCompiled == GL_FALSE) {
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
Application::ReadWholeFile(string filename)
{
	ifstream in(filename, ios::in | ios::binary);
	if(in) {
		string contents;
		in.seekg(0, ios::end);
		contents.resize(in.tellg());
		in.seekg(0, ios::beg);
		in.read(&contents[0], contents.size());
		in.close();
		return contents;
	}
	throw(errno);
}
