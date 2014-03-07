// linux: g++ -g -Wall test1.cc application.o -std=c++11 `pkg-config --cflags --libs glfw3 glew` -o test1
// windows: g++ -g -Wall test1.cc application.o -std=c++11 -lglfw3dll -lopengl32 -lglew32.dll -o test1

#include "application.h"

#include <cmath>

class Test1 : public Application
{
public:
	void Render(double currentTime) override
	{
		const GLfloat color[] = {
			(float)sin(currentTime) * 0.5f + 0.5f,
			(float)cos(currentTime) * 0.5f + 0.5f,
			0.0f, 1.0f,
		};
		glClearBufferfv(GL_COLOR, 0, color);
	}
};

DECLARE_MAIN(Test1);
