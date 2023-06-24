#pragma once
#include "utils/singleton.hh"
#include "glad/glad.h"
#include "GLFW/glfw3.h"

// Singleton Application class
class Application : public Singleton<Application>
{
	friend class Singleton<Application>;
public:
	Application(const Application&) = delete;
	Application& operator=(const Application&) = delete;
	bool shouldClose() const;
	void pollEvents() const;
	void swapBuffers() const;
	GLFWwindow* getWindow() const;
	void setKeyCallback(GLFWkeyfun callback) const;
	void setMouseButtonCallback(GLFWmousebuttonfun callback) const;
	void setCursorPosCallback(GLFWcursorposfun callback) const;
	void setScrollCallback(GLFWscrollfun callback) const;

private:
	Application();
	GLFWwindow* window = nullptr;
};
