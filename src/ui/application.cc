#include "application.hh"
#include "GLFW/glfw3.h"
#include "windows/demo-window.hh"
#include "windows/left-pannel-window.hh"
#include "windows/right-pannel-window.hh"

const ImVec4 Application::BACKGROUND_COLOR = ImVec4(40.f / 255.f, 60.f / 255.f, 36.f / 255.f, 1.f);
const ImVec4 Application::SECONDARY_COLOR = ImVec4(48.f / 255.f, 28.f / 255.f, 20.f / 255.f, 1.f);
const ImVec4 Application::TERCIARY_COLOR = ImVec4(97.f / 255.f, 53.f / 255.f, 36.f / 255.f, 1.f);
/**
 * @brief Initiliase GLFW and create a window
 */
Application::Application()
{
	// Initialise GLFW
	if (!glfwInit())
	{
		std::cerr << "Failed to initialize GLFW" << std::endl;
		return;
	}

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_STENCIL_BITS, 8);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	// Mac OS X compat
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

	// Create a window
	GLFWmonitor* monitor = glfwGetPrimaryMonitor();
	const GLFWvidmode* mode = glfwGetVideoMode(monitor);
	this->window_ = glfwCreateWindow(mode->width, mode->height, "My Tiny Town", NULL, NULL);
	if (this->window_ == NULL)
	{
		std::cerr << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return;
	}

	glfwMakeContextCurrent(window_);

	// Initialise GLAD
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cerr << "Failed to initialize GLAD" << std::endl;
		return;
	}

	// Set the viewport
	int width, height;
	glfwGetFramebufferSize(this->window_, &width, &height);
	std::cout << "viewport: width " << width - this->pannelLeftWidth_ << "x" << height << std::endl;
	std::cout << "viewport height: " << height << std::endl;
	glViewport(this->pannelLeftWidth_, 0, mode->width - this->pannelLeftWidth_, mode->height);

	unsigned int viewports[4];
	this->initialViewportWidth_ = viewports[2] = width;
	this->initialViewportHeight_ = viewports[3] = height;
}


bool Application::shouldClose() const
{
	return glfwWindowShouldClose(this->window_);
}

void Application::swapBuffers() const
{
	glfwSwapBuffers(this->window_);
}

void Application::pollEvents() const
{
	glfwPollEvents();
}

/**
 * @brief Get the window
 * @return The window
 */
GLFWwindow* Application::getWindow() const
{
	return this->window_;
}

/**
 * @brief Set the key callback function
 * @param callback The callback function
 */
void Application::setKeyCallback(GLFWkeyfun callback) const
{
	glfwSetKeyCallback(this->window_, callback);
}

/**
 * @brief Set the mouse button callback function
 * @param callback The callback function
 */
void Application::setMouseButtonCallback(GLFWmousebuttonfun callback) const
{
	glfwSetMouseButtonCallback(this->window_, callback);
}

/**
* @brief Set the cursor position callback function
* @param callback The callback function
*/
void Application::setCursorPosCallback(GLFWcursorposfun callback) const
{
	glfwSetCursorPosCallback(this->window_, callback);
}

/**
 * @brief Set the scroll callback function
 * @param callback The callback function
 */
void Application::setScrollCallback(GLFWscrollfun callback) const
{
	glfwSetScrollCallback(this->window_, callback);
}

int Application::getPannelLeftWidth() const
{
	return this->pannelLeftWidth_;
}

void Application::render() const
{
	LeftPannelWindow leftPannelWindow;
	RightPannelWindow rightPannelWindow;
	DemoWindow demoWindow;

	leftPannelWindow.render();
	rightPannelWindow.render();
	demoWindow.render();
}

int Application::getInitialViewportWidth() const
{
	return this->initialViewportWidth_;
}

int Application::getInitialViewportHeight() const
{
	return this->initialViewportHeight_;
}

