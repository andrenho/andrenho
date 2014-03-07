// linux: g++ -g -Wall testx.cc application.o -std=c++11 `pkg-config --cflags --libs glfw3 glew` -o testx
// windows: g++ -g -Wall testx.cc application.o -std=c++11 -lglfw3dll -lopengl32 -lglew32.dll -o testx

#include "application.h"

#include <cmath>
#include <iostream>

class Test : public Application
{
public:
	GLuint prog = 0, vao = 0;

	void Startup() override
	{
		prog = CompileProgram("test3_vs.glsl", "test3_fs.glsl");
		glGenVertexArrays(1, &vao);
		glBindVertexArray(vao);
	}


	void Render(double currentTime) override
	{
		const GLfloat color[] = { 0.0f, 0.2f, 0.0f, 1.0f };
		glClearBufferfv(GL_COLOR, 0, color);

		glUseProgram(prog);
		
		glDrawArrays(GL_TRIANGLES, 0, 3);
	}


	void Shutdown() override
	{
		glDeleteVertexArrays(1, &vao);
		glDeleteProgram(prog);
		glDeleteVertexArrays(1, &vao);
	}
};

DECLARE_MAIN(Test);
