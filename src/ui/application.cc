#include "application.hh"
#include "GLFW/glfw3.h"

Application::Application()
{
	// Initialise GLFW
	if (!glfwInit()) {
		std::cerr << "Failed to initialize GLFW" << std::endl;
		return;
	}

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	// Mac OS X compat
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

	// Create a window
	this->window = glfwCreateWindow(1080, 720, "MyTinyTown", NULL, NULL);
	if (this->window == NULL) {
		std::cerr << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return;
	}

	glfwMakeContextCurrent(window);

	// Initialise GLAD
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		std::cerr << "Failed to initialize GLAD" << std::endl;
		return;
	}

	// Set the viewport
	int width, height;
	glfwGetFramebufferSize(window, &width, &height);
	glViewport(0, 0, width, height);
}

bool Application::shouldClose() const
{
	return glfwWindowShouldClose(this->window);
}

void Application::swapBuffers() const
{
	glfwSwapBuffers(this->window);
}

void Application::pollEvents() const
{
	glfwPollEvents();
}

void Application::setKeyCallback(GLFWkeyfun callback) const
{
	glfwSetKeyCallback(this->window, callback);
}

void Application::setMouseButtonCallback(GLFWmousebuttonfun callback) const
{
	glfwSetMouseButtonCallback(this->window, callback);
}

void Application::setCursorPosCallback(GLFWcursorposfun callback) const
{
	glfwSetCursorPosCallback(this->window, callback);
}

void Application::setScrollCallback(GLFWscrollfun callback) const
{
	glfwSetScrollCallback(this->window, callback);
}

