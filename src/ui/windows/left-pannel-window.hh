#pragma once

#include "window.hh"

class LeftPannelWindow : public Window 
{
public:
	LeftPannelWindow() = default;
	~LeftPannelWindow() = default;
	void render() override;
};
