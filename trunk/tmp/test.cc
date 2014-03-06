// g++ test.c -std=c++11 `pkg-config --cflags --libs glfw3 glew` -o test

#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <cmath>
#include <cstdio>
#include <ctime>

int main()
{
	// initalize GLFW
	glfwInit();

	// create hints for OpenGL
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
	
	// create window
	GLFWwindow* window = glfwCreateWindow(800, 600, "OpenGL", nullptr, 
			nullptr);

	// make OpenGL context active
	glfwMakeContextCurrent(window);

	// GLEW
	glewExperimental = GL_TRUE;
	glewInit();

	// create Vertex Array Object(VAO)
	GLuint vao;
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	// create Vertex Buffer Object (VBO)
	GLuint vbo;
	glGenBuffers(1, &vbo);

	// create triangle vertices
	GLfloat vertices[] = {
		-0.8f, -0.8f,  0.0f, 1.0f, 1.0f, 1.0f,
		 0.0f, -0.8f,  0.0f, 1.0f, 1.0f, 1.0f,
		 0.8f, -0.8f,  0.0f, 1.0f, 1.0f, 1.0f,

		-0.8f,  0.0f,  0.0f, 1.0f, 1.0f, 1.0f,
		 0.0f,  0.0f,  0.5f, 1.0f, 1.0f, 1.0f,
		 0.8f,  0.0f,  0.0f, 1.0f, 1.0f, 1.0f,

		-0.8f,  0.8f,  0.0f, 1.0f, 1.0f, 1.0f,
		 0.0f,  0.8f,  0.0f, 1.0f, 1.0f, 1.0f,
		 0.8f,  0.8f, -0.5f, 1.0f, 1.0f, 1.0f,
	};

	// make VBO the active object
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices,
			GL_STATIC_DRAW);

	// create element array
	GLuint ebo;
	glGenBuffers(1, &ebo);

	GLuint elements[] = { 
		0, 3, 1,
		3, 4, 1,
		1, 4, 2,
		2, 4, 5,
		3, 6, 4,
		4, 6, 7,
		4, 7, 5,
		5, 7, 8,
	};

	// make VBO the active object
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(elements), elements, 
			GL_STATIC_DRAW);
	
	//
	// vertex shader
	//
	const char* vsource = R"VSH(

#version 150

in vec3 position;
in vec3 color;

out vec3 Color;

void main() {
	Color = color;
	gl_Position = vec4(position.x, position.y, position.z, 1.0);
}

)VSH";
	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vsource, NULL);
	glCompileShader(vertexShader);

	//
	// fragment shader
	// 
	const char* fsource = R"FSH(

#version 150

in vec3 Color;
out vec4 outColor;

void main() {
	outColor = vec4(Color, 1.0);
}

)FSH";
	GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fsource, NULL);
	glCompileShader(fragmentShader);

	// combine shaders into a program
	GLuint shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glBindFragDataLocation(shaderProgram, 0, "outColor");
	glLinkProgram(shaderProgram);
	glUseProgram(shaderProgram);

	// make link between vertex data and attributes
	GLint posAttrib = glGetAttribLocation(shaderProgram, "position");
	glEnableVertexAttribArray(posAttrib);
	glVertexAttribPointer(posAttrib, 2, GL_FLOAT, GL_FALSE, 
			6*sizeof(GLfloat), 0);

	GLint colAttrib = glGetAttribLocation(shaderProgram, "color");
	glEnableVertexAttribArray(colAttrib);
	glVertexAttribPointer(colAttrib, 3, GL_FLOAT, GL_FALSE, 
			6*sizeof(GLfloat), (void*)(3*sizeof(GLfloat)));

	// main loop
	while(!glfwWindowShouldClose(window)) {
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	        glClear(GL_COLOR_BUFFER_BIT);

		glDrawElements(GL_TRIANGLES, 24, GL_UNSIGNED_INT, 0);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	// cleanup
	glDeleteProgram(shaderProgram);
	glDeleteShader(fragmentShader);
	glDeleteShader(vertexShader);
	glDeleteBuffers(1, &ebo);
	glDeleteBuffers(1, &vbo);
	glDeleteVertexArrays(1, &vao);

	// terminate GLFW
	glfwTerminate();
}
