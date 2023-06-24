#pragma once
#include "window.hh"

/**
 * @brief Display ImGui default window.
 */
class DemoWindow : public Window
{
public:
	DemoWindow() = default;
	/**
	 * @brief the designed window.
	 */
	void render() override;
};
