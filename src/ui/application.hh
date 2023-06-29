#pragma once
#include "utils/singleton.hh"
#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include "imgui/imgui.h"
#include "scene.hh"

// Singleton Application class
class Application : public Singleton<Application>
{
	friend class Singleton<Application>;
public:
	static const ImVec4 BACKGROUND_COLOR;
	static const ImVec4 SECONDARY_COLOR; 
	static const ImVec4 TERCIARY_COLOR;
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

	/**
	 *  get the width of the left pannel
	 */
	int getPannelLeftWidth() const;

	/**
	 * Render interface
	 */
	void render(Scene& scene) const;

	int getInitialViewportWidth() const;
	int getInitialViewportHeight() const;

private:
	Application();
	GLFWwindow* window_ = nullptr;
	int pannelLeftWidth_ = 400;
	int initialViewportWidth_;
	int initialViewportHeight_;
};
