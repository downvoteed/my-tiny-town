#pragma once
#include "GLFW/glfw3.h"

class ImGuiLayer
{
public:
	// Rule of five
	/**
	 * @brief Construct a new ImGui Layer object
	 * @param window The GLFW window
	 */
	ImGuiLayer(GLFWwindow* window);
	/**
	 * @brief Destroy the ImGui Layer object. Cleanup
	 */
	~ImGuiLayer();
	ImGuiLayer(const ImGuiLayer&) = delete;
	ImGuiLayer& operator=(const ImGuiLayer&) = delete;
	ImGuiLayer(ImGuiLayer&&) = delete;
	ImGuiLayer& operator=(ImGuiLayer&&) = delete;

	/**
	 * @brief Begin a new ImGui frame
	 */
	void begin();
	/**
	 * @brief End the ImGui frame
	 */
	void end();
};