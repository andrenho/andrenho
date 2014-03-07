// linux: g++ -g -Wall testx.cc application.o -std=c++11 `pkg-config --cflags --libs glfw3 glew` -o testx
// windows: g++ -g -Wall testx.cc application.o -std=c++11 -lglfw3dll -lopengl32 -lglew32.dll -o testx

#include "application.h"

#include <cmath>

class Test : public Application
{
public:
	void Render(double currentTime) override
	{
	}
};

DECLARE_MAIN(Test);
