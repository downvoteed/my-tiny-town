#pragma once
#include "GLFW/glfw3.h"

class ImGuiLayer
{
public:
	// Rule of five
	ImGuiLayer(GLFWwindow* window);
	~ImGuiLayer();
	ImGuiLayer(const ImGuiLayer&) = delete;
	ImGuiLayer& operator=(const ImGuiLayer&) = delete;
	ImGuiLayer(ImGuiLayer&&) = delete;
	ImGuiLayer& operator=(ImGuiLayer&&) = delete;

	void begin();
	void end();
};