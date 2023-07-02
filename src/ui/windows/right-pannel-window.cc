#include "right-pannel-window.hh"
#include "imgui/imgui.h"
#include "application.hh"
#include <iostream>
#include <GLFW/glfw3.h>

RightPannelWindow::RightPannelWindow(Scene& scene) : Window(scene) { }

void RightPannelWindow::render() 
{

	if (!this->scene.getSelectedModel())
		return;

	ImGui::PushStyleColor(ImGuiCol_WindowBg, ImVec4(40.f / 255.f, 60.f / 255.f, 36.f / 255.f, 1.f));
	ImGui::PushStyleColor(ImGuiCol_TitleBg, Application::SECONDARY_COLOR);
	ImGui::PushStyleColor(ImGuiCol_TitleBgActive, Application::SECONDARY_COLOR);
	ImGui::PushStyleColor(ImGuiCol_TitleBgCollapsed, Application::SECONDARY_COLOR);
	ImGui::PushStyleColor(ImGuiCol_Button, Application::SECONDARY_COLOR);
	ImGui::PushStyleColor(ImGuiCol_Border, ImVec4(1.f, 1.f, 1.f, 1.f));
	ImGui::PushStyleColor(ImGuiCol_Button, Application::SECONDARY_COLOR);
	ImGui::PushStyleColor(ImGuiCol_ButtonHovered, Application::TERCIARY_COLOR);
	ImGui::PushStyleColor(ImGuiCol_ButtonActive, Application::TERCIARY_COLOR);

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
	std::string name = "No model selected";
	std::string textureName = "No model selected";
	float posX = 0, posY = 0, posZ = 0;
	int id = 1;
	if (this->scene.getSelectedModel())
	{
		Model* model = this->scene.getSelectedModel();
		id = model->getID();
		name = model->getName().c_str();
		posX = model->getPosition().x;
		posY = model->getPosition().y;
		posZ = model->getPosition().z;
		textureName = model->getTextureName();
		
	}

	ImGui::Text("Name: %s (%d)" , name.c_str(), id);
	ImGui::Text("Pos: (x: %.2f, y: %.2f, z: %.2f)", posX, posY, posZ);
	ImGui::Text("Scale: 0");
	ImGui::Text("Texture: %s", textureName.c_str());
	ImGui::Text("Rotate:");
	
	if (ImGui::Button("-180"))
	{
		this->scene.getSelectedModel()->rotate(glm::radians(-180.f), glm::vec3(0, 1, 0));
	}
	ImGui::SameLine();
	if (ImGui::Button("-90"))
	{
		this->scene.getSelectedModel()->rotate(glm::radians(-90.f), glm::vec3(0, 1, 0));
	}
	ImGui::SameLine();
	if (ImGui::Button("90"))
	{
		this->scene.getSelectedModel()->rotate(glm::radians(90.f), glm::vec3(0, 1, 0));
	}
	ImGui::SameLine();
	if (ImGui::Button("180"))
	{
		this->scene.getSelectedModel()->rotate(glm::radians(180.f), glm::vec3(0, 1, 0));
	}
	ImGui::End();

	ImGui::PopStyleColor();
	ImGui::PopStyleColor();
	ImGui::PopStyleColor();
	ImGui::PopStyleColor();
	ImGui::PopStyleColor();
	ImGui::PopStyleColor();
	ImGui::PopStyleColor();
	ImGui::PopStyleColor();
	ImGui::PopStyleColor();

	ImGui::PopStyleVar();
	ImGui::PopStyleVar();
}
