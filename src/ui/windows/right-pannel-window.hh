#pragma once

#include "window.hh"

class RightPannelWindow : public Window 
{
public:
	RightPannelWindow() = default;
	~RightPannelWindow() = default;
	void render() override;
};
