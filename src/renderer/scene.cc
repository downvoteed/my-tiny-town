#include "scene.hh"
#include "camera/camera.hh"
#include "frame-buffer.hh"
#include <glm/glm.hpp>
#include <GLFW/glfw3.h>
#include "imgui/imgui.h"
#include "application.hh"
#include "utils/utils.hh"

static bool mouseButtonPressed = false;

Scene::Scene() : camera_(35.0f, 1280.0f / 780.0f, 0.1f, 1000.0f), frameBuffer_()
{
	camera_.setYaw(-90.0f);
    camera_.setPitch(-90.f); // Make the camera look straight ahead
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

		for (const auto& [_, tempModel] : this->models_)
		{
			tempModel->setSelected(false);
			if (models_.find(objectID) != models_.end())
				this->setSelectedModel(objectID);
		}
		if (models_.find(objectID) != models_.end())
		{
			auto model = this->models_.at(objectID);
			bool isAlreadySelected = model->isSelected();

			if (!isAlreadySelected && objectID != 1)
				model->setSelected(true);
		}
		else
		{
			this->setSelectedModel(0);
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
			model->draw(false);
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

void Scene::setSelectedModel(const size_t id)
{
	if (id == 0)
		this->selectedModel_ = nullptr;
	else
		this->selectedModel_ = this->models_.at(id);
}

Model* Scene::getSelectedModel()
{
	return this->selectedModel_;
}
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset) 
{
	// Get the user pointer and assume it is a Scene instance
	Scene* scene = static_cast<Scene*>(glfwGetWindowUserPointer(window));

	// Call the member function
	scene->processScroll(xoffset, yoffset);
}
void cursor_position_callback(GLFWwindow* window, double xpos, double ypos)
{
	static Model* lastSelectedModel = nullptr;
	static double lastX = 0.0;
	static double lastY = 0.0;

	Scene* scene = static_cast<Scene*>(glfwGetWindowUserPointer(window));
	Model* selectedModel = scene->getSelectedModel();

	if (!ImGui::GetIO().WantCaptureMouse && glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS)
	{
		if (selectedModel != lastSelectedModel)
		{
			lastX = xpos;
			lastY = ypos;
			lastSelectedModel = selectedModel;
		}

		if (selectedModel == nullptr) { return; }

		double dx = xpos - lastX;
		double dy = ypos - lastY;

		glm::vec3 position = selectedModel->getPosition();
		position.x -= dx * 0.01f;
		position.y += dy * 0.1f;
		selectedModel->setPosition(position);

		lastX = xpos;
		lastY = ypos;
	}
	else
	{
		lastSelectedModel = nullptr;
	}
}


void Scene::processScroll(double xoffset, double yoffset) 
{
	// handle scroll event...
	camera_.processMouseScroll(yoffset);
}

