#ifndef APPLICATION_H
#define APPLICATION_H

#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <string>
#include <vector>
using namespace std;

#define DECLARE_MAIN(Klass) int main() { Klass k; k.Startup(); k.Run(); k.Shutdown(); }

class Application {
public:
	void Run();

protected:
	Application();
	~Application();

	virtual void Startup() { }
	virtual void Render(double currentTime) { }
	virtual void Shutdown() { }

	GLuint CompileProgram(string vs_src, string fs_src);

private:
	string ReadWholeFile(string filename);

	GLFWwindow* window;
};

#endif
