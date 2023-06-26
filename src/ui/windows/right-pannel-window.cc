#include "right-pannel-window.hh"
#include "imgui/imgui.h"
#include "application.hh"
#include <iostream>
#include <GLFW/glfw3.h>

void RightPannelWindow::render() 
{

	ImGui::PushStyleColor(ImGuiCol_WindowBg, ImVec4(40.f / 255.f, 60.f / 255.f, 36.f / 255.f, 1.f));
	ImGui::PushStyleColor(ImGuiCol_TitleBg, Application::SECONDARY_COLOR);
	ImGui::PushStyleColor(ImGuiCol_TitleBgActive, Application::SECONDARY_COLOR);
	ImGui::PushStyleColor(ImGuiCol_TitleBgCollapsed, Application::SECONDARY_COLOR);
	ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
	ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 5.0f);
	ImGui::Begin("Model properties", nullptr, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove);
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
	ImGui::PopStyleColor();
	ImGui::PopStyleColor();
	ImGui::PopStyleColor();
	ImGui::PopStyleVar();
	ImGui::PopStyleVar();
}
