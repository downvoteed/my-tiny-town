#include "left-pannel-window.hh"
#include "imgui/imgui.h"
#include "ImGuiFileDialog/ImGuiFileDialog.h"
#include "application.hh"
#include <iostream>
#include <GLFW/glfw3.h>

void LeftPannelWindow::render() 
{
	ImGui::PushStyleColor(ImGuiCol_WindowBg, Application::BACKGROUND_COLOR);
	ImGui::PushStyleColor(ImGuiCol_Button, Application::SECONDARY_COLOR);
	ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 5.0f);
	ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
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

	// open Dialog 
	if (ImGui::Button("Open File Dialog"))
		ImGuiFileDialog::Instance()->OpenDialog("ChooseFileDlgKey", "Choose File", ".cpp,.h,.hpp", ".");

	// display
	if (ImGuiFileDialog::Instance()->Display("ChooseFileDlgKey"))
	{
		// action if OK
		if (ImGuiFileDialog::Instance()->IsOk())
		{
			std::string filePathName = ImGuiFileDialog::Instance()->GetFilePathName();
			std::string filePath = ImGuiFileDialog::Instance()->GetCurrentPath();
			// action
		}

		// close
		ImGuiFileDialog::Instance()->Close();
	}

	ImGui::SetWindowPos(pos);
	ImFont* font = ImGui::GetIO().Fonts->Fonts[1];

	ImGui::PushFont(font);
	ImGui::Text("MY TINY TOWN");
	ImGui::PopFont();
	ImGui::End();
	ImGui::PopStyleColor();
	ImGui::PopStyleColor();
	ImGui::PopStyleVar();
	ImGui::PopStyleVar();
}
