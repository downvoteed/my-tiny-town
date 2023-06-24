#pragma once

/**
 * @brief interface
 */
class Window
{
public:
	Window() = default;
	~Window() = default;
	Window(const Window&) = delete;
	Window& operator=(const Window&) = delete;
	Window(Window&&) = delete;

	/**
	 * @brief Render the designed window.
	 */
	virtual void render() = 0;
};
