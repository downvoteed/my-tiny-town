#include "right-pannel-window.hh"
#include "imgui/imgui.h"
#include "application.hh"
#include <iostream>
#include <GLFW/glfw3.h>

RightPannelWindow::RightPannelWindow(Scene& scene) : Window(scene) 
{

	unsigned char* data = nullptr;
	int width = 0; int height = 0; int channels = 0;

	// Image B
	data = stbi_load("assets/ImageB.png", &width, &height, &channels, 4);
	if (data == nullptr)
		std::cerr << "Failed to load image" << std::endl;

	GL_CALL(glGenTextures(1, &this->imageB));
	GL_CALL(glBindTexture(GL_TEXTURE_2D, this->imageB));
	GL_CALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR));
	GL_CALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR));
	GL_CALL(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data));
	GL_CALL(glBindTexture(GL_TEXTURE_2D, 0));

	stbi_image_free(data);

	// Image F
	data = stbi_load("assets/ImageF.png", &width, &height, &channels, 4);
	if (data == nullptr)
		std::cerr << "Failed to load image" << std::endl;

	GL_CALL(glGenTextures(1, &this->imageF));
	GL_CALL(glBindTexture(GL_TEXTURE_2D, this->imageF));
	GL_CALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR));
	GL_CALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR));
	GL_CALL(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data));
	GL_CALL(glBindTexture(GL_TEXTURE_2D, 0));

	stbi_image_free(data);

	// Image L
	data = stbi_load("assets/ImageL.png", &width, &height, &channels, 4);
	if (data == nullptr)
		std::cerr << "Failed to load image" << std::endl;

	GL_CALL(glGenTextures(1, &this->imageL));
	GL_CALL(glBindTexture(GL_TEXTURE_2D, this->imageL));
	GL_CALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR));
	GL_CALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR));
	GL_CALL(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data));
	GL_CALL(glBindTexture(GL_TEXTURE_2D, 0));

	stbi_image_free(data);

	// Image R
	data = stbi_load("assets/ImageR.png", &width, &height, &channels, 4);
	if (data == nullptr)
		std::cerr << "Failed to load image" << std::endl;

	GL_CALL(glGenTextures(1, &this->imageR));
	GL_CALL(glBindTexture(GL_TEXTURE_2D, this->imageR));
	GL_CALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR));
	GL_CALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR));
	GL_CALL(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data));
	GL_CALL(glBindTexture(GL_TEXTURE_2D, 0));

	stbi_image_free(data);
}

void RightPannelWindow::render()
{
	auto& models = this->scene.getModels();
	Model* currentModel = this->scene.getSelectedModel();

	if (currentModel == nullptr)
		// get objetID = 1
		currentModel = models.find(1)->second;

	if (currentModel == nullptr) { return; }

	ImGui::PushStyleColor(ImGuiCol_WindowBg, ImVec4(40.f / 255.f, 60.f / 255.f, 36.f / 255.f, 1.f));
	ImGui::PushStyleColor(ImGuiCol_TitleBg, Application::SECONDARY_COLOR);
	ImGui::PushStyleColor(ImGuiCol_TitleBgActive, Application::SECONDARY_COLOR);
	ImGui::PushStyleColor(ImGuiCol_TitleBgCollapsed, Application::SECONDARY_COLOR);
	ImGui::PushStyleColor(ImGuiCol_Button, Application::SECONDARY_COLOR);
	ImGui::PushStyleColor(ImGuiCol_Border, ImVec4(1.f, 1.f, 1.f, 1.f));
	ImGui::PushStyleColor(ImGuiCol_Button, Application::SECONDARY_COLOR);
	ImGui::PushStyleColor(ImGuiCol_ButtonHovered, Application::TERCIARY_COLOR);
	ImGui::PushStyleColor(ImGuiCol_ButtonActive, Application::TERCIARY_COLOR);
	ImGui::PushStyleColor(ImGuiCol_SliderGrab, Application::TERCIARY_COLOR);

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
	Model* model = currentModel;
	id = model->getID();
	name = model->getName().c_str();
	posX = model->getPosition().x;
	posY = model->getPosition().y;
	posZ = model->getPosition().z;
	textureName = model->getTextureName();

	ImGui::Text("Name: %s (%d)" , name.c_str(), id);
	ImGui::Text("Pos: (x: %.2f, y: %.2f, z: %.2f)", posX, posY, posZ);
	ImGui::Text("Texture: %s", textureName.c_str());

	int width = 0; int height = 0; int channels = 0;
	unsigned char* data = nullptr;
	GLuint texture = 0;

	if (model->getID() != 1)
	{

		ImGui::Text("Rotate:");

		ImVec2 imageSize = ImVec2(20, 20);

		if (ImGui::ImageButton((void*)(intptr_t)this->imageF, imageSize, ImVec2(0, 1), ImVec2(1, 0)))
		{
			glm::mat4 original = model->getOriginalModelMatrix();
			model->setModelMatrix(original);
		}
		ImGui::SameLine();
		if (ImGui::ImageButton((void*)(intptr_t)this->imageB, imageSize, ImVec2(0, 1), ImVec2(1, 0)))
		{
			glm::mat4 original = model->getOriginalModelMatrix();
			glm::mat4 newMatrix = glm::rotate(original, glm::radians(180.f), glm::vec3(0, 1, 0));
			model->setModelMatrix(newMatrix);
		}
		ImGui::SameLine();
		if (ImGui::ImageButton((void*)(intptr_t)this->imageL, imageSize))
		{
			glm::mat4 original = model->getOriginalModelMatrix();
			glm::mat4 newMatrix = glm::rotate(original, glm::radians(-90.f), glm::vec3(0, 1, 0));
			model->setModelMatrix(newMatrix);
		}
		ImGui::SameLine();
		if (ImGui::ImageButton((void*)(intptr_t)this->imageR, imageSize))
		{
			glm::mat4 original = model->getOriginalModelMatrix();
			glm::mat4 newMatrix = glm::rotate(original, glm::radians(90.f), glm::vec3(0, 1, 0));
			model->setModelMatrix(newMatrix);
		}

	}
	// center text

	ImGui::PushStyleColor(ImGuiCol_FrameBg, Application::SECONDARY_COLOR);
	ImGui::NewLine();
	int center = (ImGui::GetWindowSize().x - ImGui::CalcTextSize("Scale:").x) / 2;
	ImGui::SetCursorPosX(center);
	ImGui::Text("Scale:");
	ImGui::Text("x :");
	float scaleFactorX = model->getSize().x / model->getInitialSize().x;
	if (ImGui::SliderFloat("##x", &scaleFactorX, 0.1f, 5.0f))
	{
		glm::vec3 currentScale = model->getSize() / model->getInitialSize();
		glm::vec3 newSize = model->getInitialSize() * glm::vec3(scaleFactorX, currentScale.y, currentScale.z);
		model->setSize(newSize);
	}
	ImGui::Text("y :");
	float scaleFactorY = model->getSize().y / model->getInitialSize().y;
	if (ImGui::SliderFloat("##y", &scaleFactorY, 0.1f, 5.0f))
	{
		glm::vec3 currentScale = model->getSize() / model->getInitialSize();
		glm::vec3 newSize = model->getInitialSize() * glm::vec3(currentScale.x, scaleFactorY, currentScale.z);
		model->setSize(newSize);
	}
	if (model->getID() != 1)
	{
		ImGui::Text("z :");
		float scaleFactorZ = model->getSize().z / model->getInitialSize().z;
		if (ImGui::SliderFloat("##z", &scaleFactorZ, 0.1f, 5.0f))
		{
			glm::vec3 currentScale = model->getSize() / model->getInitialSize();
			glm::vec3 newSize = model->getInitialSize() * glm::vec3(currentScale.x, currentScale.y, scaleFactorZ);
			model->setSize(newSize);
		}
	}
	ImGui::PopStyleColor();
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
	ImGui::PopStyleColor();

	ImGui::PopStyleVar();
	ImGui::PopStyleVar();
}
