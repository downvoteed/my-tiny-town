#include <iostream>
#include "ui/application.hh"

int main()
{
	std::cout << "Hello World!\n";
	Application* app = Application::instance();

	while (!app->shouldClose())
	{
		app->pollEvents();
		app->swapBuffers();
	}
	glfwTerminate();
	return 0;
}