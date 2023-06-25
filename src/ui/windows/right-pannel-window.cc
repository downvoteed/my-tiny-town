#include "right-pannel-window.hh"
#include "imgui/imgui.h"
#include "application.hh"
#include <iostream>
#include <GLFW/glfw3.h>

void RightPannelWindow::render() 
{

	ImGui::PushStyleColor(ImGuiCol_WindowBg, ImVec4(40.f / 255.f, 60.f / 255.f, 36.f / 255.f, 1.f));
	ImGui::Begin("right pannel", nullptr, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove);
	// remove border

	{
		short margin = 50;
		int pannelWidth, pannelHeight;
		pannelWidth = 250;
		pannelHeight = 250;
		auto size = ImVec2(pannelWidth, pannelHeight);
		ImGui::SetWindowSize(size);
		{
			int windowWidth, windowHeight;
			GLFWwindow* mainWindow = Application::instance()->getWindow();
			ImVec2 pos;
			glfwGetWindowSize(mainWindow, &windowWidth, &windowHeight);
			pos.x = windowWidth - pannelWidth - margin;
			pos.y = margin;
			ImGui::SetWindowPos(pos);
		}
	}

	// change font
	ImGui::Text("Hello from right pannel");
	ImGui::End();
	ImGui::PopStyleColor();
}
