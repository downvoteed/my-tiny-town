#pragma once

#include "window.hh"
#include <GLFW/glfw3.h>

class LeftPannelWindow : public Window 
{
public:
	LeftPannelWindow(Scene& scene);
	~LeftPannelWindow();
	LeftPannelWindow(const LeftPannelWindow&) = delete;
	LeftPannelWindow& operator=(const LeftPannelWindow&) = delete;
	LeftPannelWindow(LeftPannelWindow&&) = delete;
	LeftPannelWindow& operator=(LeftPannelWindow&&) = delete;
	void render() override;

private:
	unsigned char* data_;
	int width_;
	int height_;
	int channels_;
	GLuint texture_;
};
