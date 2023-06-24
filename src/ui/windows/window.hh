#pragma once

class Window
{
public:
	Window() = default;
	~Window() = default;
	Window(const Window&) = delete;
	Window& operator=(const Window&) = delete;
	Window(Window&&) = delete;

	virtual void render() = 0;
};
