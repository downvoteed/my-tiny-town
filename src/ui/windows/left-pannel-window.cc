#include "left-pannel-window.hh"
#include "imgui/imgui.h"
#include "application.hh"
#include <iostream>
#include <GLFW/glfw3.h>

void LeftPannelWindow::render() 
{
	ImGui::PushStyleColor(ImGuiCol_WindowBg, ImVec4(40.f / 255.f, 60.f / 255.f, 36.f / 255.f, 1.f));
	ImGui::Begin("left pannel", nullptr, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove);
	// remove border


	ImVec2 pos;
	pos.x = 0;
	pos.y = 0;

	GLFWwindow* mainWindow = Application::instance()->getWindow();
	// get size from glfw window
	{
		int width, height;
		glfwGetWindowSize(mainWindow, &width, &height);
		auto size = ImVec2(Application::instance()->getPannelLeftWidth(), height);
		ImGui::SetWindowSize(size);
	}
	// change background color

	ImGui::SetWindowPos(pos);
	// change font
	ImGui::Text("Hello from left pannel");
	ImGui::End();
	ImGui::PopStyleColor();
}
