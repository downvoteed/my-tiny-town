#pragma once
#include "scene.hh"

/**
 * @brief interface
 */
class Window
{
public:
	Window(Scene& s): scene(s)
	{}
	~Window() = default;
	Window(const Window&) = delete;
	Window& operator=(const Window&) = delete;
	Window(Window&&) = delete;
	Window& operator=(Window&&) = delete;
	/**
	 * @brief Render the designed window.
	 */
	virtual void render() = 0;

	Scene& scene;
};
