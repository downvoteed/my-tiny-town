#pragma once
#include "utils/singleton.hh"
#include "glad/glad.h"
#include "GLFW/glfw3.h"

// Singleton Application class
class Application : public Singleton<Application>
{
	friend class Singleton<Application>;
public:
	/**
	 * @brief Initiliase GLFW and create a window
	 */
	Application(const Application&) = delete;
	Application& operator=(const Application&) = delete;
	bool shouldClose() const;
	void pollEvents() const;
	void swapBuffers() const;
	/**
	 * @brief Get the window
	 * @return The window
	 */
	GLFWwindow* getWindow() const;
	/**
	 * @brief Set the key callback function
	 * @param callback The callback function
	 */
	void setKeyCallback(GLFWkeyfun callback) const;
	/**
	 * @brief Set the mouse button callback function
	 * @param callback The callback function
	 */
	void setMouseButtonCallback(GLFWmousebuttonfun callback) const;
	/**
	* @brief Set the cursor position callback function
	* @param callback The callback function
	*/
	void setCursorPosCallback(GLFWcursorposfun callback) const;
	/**
	 * @brief Set the scroll callback function
	 * @param callback The callback function
	 */
	void setScrollCallback(GLFWscrollfun callback) const;

private:
	Application();
	GLFWwindow* window = nullptr;
};
