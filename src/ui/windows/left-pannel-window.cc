#include "left-pannel-window.hh"
#include "imgui/imgui.h"
#include "ImGuiFileDialog/ImGuiFileDialog.h"
#include "application.hh"
#include <iostream>
#include <GLFW/glfw3.h>

const short buttonMarginLR = 35;
const short buttonMarginTB = 20;
const short buttonWidth = 70;
const short buttonHeight = 40;

LeftPannelWindow::LeftPannelWindow(Scene& scene) : Window(scene) {}

void LeftPannelWindow::render() 
{
	//
	ImGui::PushStyleColor(ImGuiCol_WindowBg, Application::BACKGROUND_COLOR);
	ImGui::PushStyleColor(ImGuiCol_Button, Application::SECONDARY_COLOR);
	ImGui::PushStyleColor(ImGuiCol_Border, ImVec4(1.f, 1.f, 1.f, 1.f));
	ImGui::PushStyleColor(ImGuiCol_Button, Application::SECONDARY_COLOR);
	ImGui::PushStyleColor(ImGuiCol_ButtonHovered, Application::TERCIARY_COLOR);
	ImGui::PushStyleColor(ImGuiCol_ButtonActive, Application::TERCIARY_COLOR);
	ImGui::PushStyleColor(ImGuiCol_MenuBarBg, Application::SECONDARY_COLOR);

	ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 5.0f);
	ImGui::PushStyleVar(ImGuiStyleVar_FrameRounding, 8.0f);
	ImGui::PushStyleVar(ImGuiStyleVar_FrameBorderSize, 1.0f);
	ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
	ImGui::PushStyleVar(ImGuiStyleVar_ChildRounding, 5.0f);

	ImGui::Begin("left pannel", nullptr, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove);
	// remove border


	GLFWwindow* mainWindow = Application::instance()->getWindow();
	// get size from glfw window
	{
		int width, height;
		glfwGetWindowSize(mainWindow, &width, &height);
		auto size = ImVec2(Application::instance()->getPannelLeftWidth(), height);
		ImGui::SetWindowSize(size);
	}
	// change background color
	{
		ImVec2 pos;
		pos.x = buttonMarginLR;
		pos.y = buttonMarginTB;
		// open Dialog 
		ImGui::SetCursorPosX(pos.x);
		ImGui::SetCursorPosY(pos.y);
		if (ImGui::Button("Open", ImVec2(buttonWidth, buttonHeight)))
			ImGuiFileDialog::Instance()->OpenDialog("ChooseFileDlgKey", "Choose File", ".obj", ".");
	}

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

	{
		ImVec2 pos;
		pos.x = Application::instance()->getPannelLeftWidth() - (buttonWidth + buttonMarginLR);
		pos.y = buttonMarginTB;
		// open Dialog 
		ImGui::SetCursorPosX(pos.x);
		ImGui::SetCursorPosY(pos.y);
		if (ImGui::Button("Save", ImVec2(buttonWidth, buttonHeight)))
		{
			// TODO: actually save scene (serialize)
		}
	}

	ImGui::NewLine();

	{
		ImVec2 pos;
		pos.x = 0;
		pos.y = 0;
		ImGui::SetWindowPos(pos);
		ImFont* font = ImGui::GetIO().Fonts->Fonts[1];

		ImGui::PushFont(font);
		auto textSize = ImGui::CalcTextSize("MY TINY TOWN");
		auto center = ImVec2(Application::instance()->getPannelLeftWidth() / 2 - textSize.x / 2, 0);
		ImGui::SetCursorPosX(center.x);
		ImGui::Text("MY TINY TOWN");
		ImGui::PopFont();
	}

	// Gallery preview obj

	ImGui::NewLine();

	ImGui::SetCursorPosX(buttonMarginLR);
	ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(0, 10));
	ImGui::BeginChild("left pannel child", ImVec2(Application::instance()->getPannelLeftWidth() - buttonMarginLR * 2, 700),
		true, ImGuiWindowFlags_MenuBar);

	if (ImGui::BeginMenuBar())
	{
		ImGui::PopStyleVar();
		ImGui::Text("Assets");
		ImGui::SetCursorPosX(Application::instance()->getPannelLeftWidth() - buttonMarginLR * 2 - buttonWidth - 10);
		auto currenPos = ImGui::GetCursorPos();
		ImGui::SetCursorPosY(currenPos.y + 7);
		if (ImGui::Button("Import",(ImVec2(buttonWidth, 25))))
		{
			// Handle button press
		}
		ImGui::EndMenuBar();
	}
	else
	{
		// to pop in any case
		ImGui::PopStyleVar();
	}

	ImGui::EndChild();

	ImGui::End();

	ImGui::PopStyleColor();
	ImGui::PopStyleColor();
	ImGui::PopStyleColor();
	ImGui::PopStyleColor();
	ImGui::PopStyleColor();
	ImGui::PopStyleColor();
	ImGui::PopStyleColor();

	ImGui::PopStyleVar();
	ImGui::PopStyleVar();
	ImGui::PopStyleVar();
	ImGui::PopStyleVar();
	ImGui::PopStyleVar();
}
