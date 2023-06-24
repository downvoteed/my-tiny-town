#pragma once
#include "window.hh"

class DemoWindow : public Window
{
public:
	DemoWindow() = default;
	void render() override;
};
