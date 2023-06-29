#pragma once

#include "window.hh"

class RightPannelWindow : public Window 
{
public:
	RightPannelWindow(Scene& scene);
	~RightPannelWindow() = default;
	void render() override;
};
