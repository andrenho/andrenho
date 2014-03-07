// linux: g++ -g -Wall testx.cc application.o -std=c++11 `pkg-config --cflags --libs glfw3 glew` -o testx
// windows: g++ -g -Wall testx.cc application.o -std=c++11 -lglfw3dll -lopengl32 -lglew32.dll -o testx

#include "application.h"

#include <cmath>

class Test : public Application
{
public:
	GLuint prog = 0, vao = 0;

	void Startup() override
	{
		prog = CompileProgram("test2_vs.glsl", "test2_fs.glsl");
		glGenVertexArrays(1, &vao);
		glBindVertexArray(vao);
	}

	void Render(double currentTime) override
	{
		const GLfloat color[] = {
			(float)sin(currentTime) * 0.5f + 0.5f,
			(float)cos(currentTime) * 0.5f + 0.5f,
			0.0f, 1.0f,
		};
		glClearBufferfv(GL_COLOR, 0, color);

		glUseProgram(prog);
		
		glPointSize(40.0f);
		glDrawArrays(GL_POINTS, 0, 1);
	}

	void Shutdown() override
	{
		glDeleteVertexArrays(1, &vao);
		glDeleteProgram(prog);
		glDeleteVertexArrays(1, &vao);
	}
};

DECLARE_MAIN(Test);
