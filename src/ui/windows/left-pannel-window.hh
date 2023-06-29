#pragma once

#include "window.hh"

class LeftPannelWindow : public Window 
{
public:
	LeftPannelWindow(Scene& scene);
	~LeftPannelWindow() = default;
	void render() override;
};
