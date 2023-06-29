#include "scene.hh"
#include "camera/camera.hh"
#include "frame-buffer.hh"
#include <glm/glm.hpp>
#include <GLFW/glfw3.h>
#include "imgui/imgui.h"
#include "application.hh"
#include "utils/utils.hh"

static bool mouseButtonPressed = false;

Scene::Scene() : camera_(35.0f, 800.0f / 600.0f, 0.1f, 100.0f), frameBuffer_()
{
	this->camera_.setPosition(glm::vec3(0.0f, 10.0f, 0.0f));

	this->camera_.setPitch(-90.0f);
	this->camera_.setYaw(-90.0f);
	this->camera_.setPosition(glm::vec3(0.0f, 20.0f, 0.0f));

}

void Scene::addModel(size_t id, Model* model)
{
	this->models_.insert({ id, model });
}

void Scene::draw()
{
	glm::mat4 view = this->camera_.getViewMatrix();
	glm::mat4 projection = camera_.getProjectionMatrix();
	
    bool mouseButtonCurrentlyPressed = glfwGetMouseButton(Application::instance()->getWindow(), GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS;

	if (!ImGui::GetIO().WantCaptureMouse && mouseButtonCurrentlyPressed && !mouseButtonPressed)
	{
		FrameBuffer& fbo = this->getFrameBuffer();
		fbo.bind();

		for (const auto& [_, model] : this->models_)
		{
			model->setProjectionMatrix(projection);
			model->setViewMatrix(view);
			model->draw(true);

		}

		unsigned char pixelColor[3];
		double mouseX, mouseY;

		glfwGetCursorPos(Application::instance()->getWindow(), &mouseX, &mouseY);

		int currentWidth, currentHeight;
		glfwGetFramebufferSize(Application::instance()->getWindow(), &currentWidth, &currentHeight);

		glViewport(Application::instance()->getPannelLeftWidth(), 0, currentWidth - Application::instance()->getPannelLeftWidth(), currentHeight);

		int textureX = static_cast<int>(mouseX);
		int textureY = static_cast<int>((currentHeight - mouseY));

		std::cout << textureX << " " << textureY << std::endl;

		glReadPixels(textureX, textureY, 1, 1, GL_RGB, GL_UNSIGNED_BYTE, pixelColor);

		glm::vec3 color = glm::vec3(pixelColor[0], pixelColor[1], pixelColor[2]);
		std::cout << "Color: " << color.x << " " << color.y << " " << color.z << std::endl;

		size_t objectID = colorToId(color);
		std::cout << "Object ID: " << objectID << std::endl;


		auto model = this->models_.at(objectID);
		bool isAlreadySelected = model->isSelected();
		for (const auto& [_, tempModel] : this->models_)
			tempModel->setSelected(false);


		if (objectID != 1 && models_.find(objectID) != models_.end())
		{
			if (!isAlreadySelected)
				model->setSelected(true);
		}

		fbo.unbind();
	}
	for (const auto& [_, model] : this->models_)
	{
		model->setProjectionMatrix(projection);
		model->setViewMatrix(view);
		if (model->isSelected())
		{
			model->drawStencil();
			model->drawOutline();
		}
		else
			model->draw(false);
	}
	mouseButtonPressed = mouseButtonCurrentlyPressed;



}

Camera& Scene::getCamera()
{
	return this->camera_;
}

FrameBuffer& Scene::getFrameBuffer()
{
	return this->frameBuffer_;
}
